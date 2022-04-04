/*
 * @file: 
 * @copyright: 2012 - 2028 ByteDance. All Rights Reserved
 * @Author: guanlei
 * @Date: 2021-11-08 16:45:54
 * @brief: 
 */
#include "wsstackrecorder.h"
#include "shmmgr.h"
#include <limits.h>
#include <unistd.h>

CWSStackRecorder::SCallQueue* CWSStackRecorder::sm_pstQueue = NULL;

EWSShmErrCode WS_GetStackRecorder(int nShmKey, 
    const char* pszDumpFileName, bool bDumpPrevInstance)
{
    if(nShmKey <= 0 || NULL == pszDumpFileName)
    {
        return WS_WRONG_PARAM;
    }
    
    if(false == CWSStackRecorder::Instance().Init(nShmKey, 
        pszDumpFileName, bDumpPrevInstance))
    {
        return WS_SYSTEM_ERROR;
    }

    return WS_SUCCESS;
}

CWSStackRecorder::CWSStackRecorder()
{
    m_nShmKey       = 0;
    m_pShm          = NULL;
    m_pcContentBuf  = NULL;
    sm_pstQueue      = NULL;
}

CWSStackRecorder::~CWSStackRecorder()
{
}

bool CWSStackRecorder::Init(int nShmKey, const char* pszDumpFileName, 
    bool bDumpPrevInstance)
{
    if(nShmKey <= 0)
    {
        return false;
    }

    uint32 dwSize = sizeof(SCallQueue) + WS_RECORD_BUF_LEN + 32;
    EWSShmErrCode nRet = WS_CreateShm(nShmKey, dwSize, &m_pShm);
    if(NULL == m_pShm)
    {
        return false;
    }

    m_strDumpFileName   = pszDumpFileName;
    sm_pstQueue         = (SCallQueue*)m_pShm;
    m_pcContentBuf      = (char*)m_pShm + sizeof(SCallQueue) + 16;
    m_nShmKey           = nShmKey;

    if(true == bDumpPrevInstance && WS_SHM_ALREADY_EXISTS == nRet)
    {
        _SaveToFile();
    }

    memset(m_pShm, 0, dwSize);
    return true;
}

void CWSStackRecorder::Uninit()
{
    if(m_nShmKey <= 0)
    {
        return;
    }

    WS_DeleteShm(m_nShmKey);
    m_nShmKey = 0;
}

bool CWSStackRecorder::_SaveToFile()
{
    if(NULL == sm_pstQueue)
    {
        return false;
    }

    char szPath[PATH_MAX - 1000];
    if (NULL == getcwd(szPath, PATH_MAX-1000))
    {
        return false;
    }

    char szFile[PATH_MAX];
    snprintf(szFile, PATH_MAX, "%s_%d.stack", szPath, (int)time(NULL));

    FILE* fp = fopen(szFile, "w+");
    if(NULL == fp)
    {
        return false;
    }

    char szText[WS_CALLSTACK_LEN * 32] = {0};
    char szAddr[32] = {0};
    snprintf(szText, sizeof(szText), "Len: %u\r\nBase\r\n", 
        sm_pstQueue->m_dwTop);
    for(uint32 n = 0; n < sm_pstQueue->m_dwTop; n++)
    {
        if(n >= WS_CALLSTACK_LEN)
        {
            break;
        }

        snprintf(szAddr, 32, "0x%016llx\r\n",(long long unsigned int)sm_pstQueue->m_adwStack[n]);
        strcat(szText, szAddr);
    }
    strcat(szText, "Top\r\n");

    if(sm_pstQueue->m_dwTop < WS_CALLSTACK_LEN)
    {
        snprintf(szAddr, 32, "0x%016llx\r\n",
            (long long unsigned int)sm_pstQueue->m_adwStack[sm_pstQueue->m_dwTop]);
        strcat(szText, szAddr);
    }

    int retval = fwrite(szText, 1, strnlen(szText, sizeof(szText)), fp);
    (void)retval;
    fclose(fp);
    fp = NULL;

    return true;
}
