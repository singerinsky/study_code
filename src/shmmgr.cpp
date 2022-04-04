/*
 * @file: 
 * @copyright: 2012 - 2028 ByteDance. All Rights Reserved
 * @Author: guanlei
 * @Date: 2021-11-08 17:13:14
 * @brief: 
 */
#include "shmmgr.h"
#include <sys/types.h>
#include <sys/shm.h>
#include <assert.h>

CShmMgr::CShmMgr()
{
}

CShmMgr::~CShmMgr()
{
    for(auto& kv: m_oShmHandle)
    {
        delete kv.second;
    }

    m_oShmHandle.clear();
}

void CShmMgr::Release()
{
}

SShmItem* CShmMgr::GetShmItem(int nKey)
{
    CShmMap::iterator it = m_oShmHandle.find(nKey);
    if(it != m_oShmHandle.end() )
    {
        return it->second;
    }
    return NULL;
}

bool CShmMgr::AddShmItem(SShmItem* pstShmitem)
{
    if(NULL == pstShmitem)
    {
        return false;
    }

    if(GetShmItem(pstShmitem->m_nKey) != NULL)
    {
        return false;
    }

    m_oShmHandle[pstShmitem->m_nKey] = pstShmitem;
    return true;
}

bool CShmMgr::DeleteShm(int nKey)
{
    SShmItem* pstItem = GetShmItem(nKey);
    if(NULL == pstItem)
    {
        return false;
    }

    pstItem->m_nRef--;
    if(pstItem->m_nRef <= 0)
	{
		shmdt(pstItem->m_pShm);

        if(true == pstItem->m_bCreat)
        {

			shmctl(pstItem->m_nHandle, IPC_RMID, NULL);
        }
        delete pstItem;
        m_oShmHandle.erase(nKey);
    }

    return true;
}

int CShmMgr::GetItemSize()
{
    return (int)m_oShmHandle.size();
}


void* CheckExist(int nKey, uint32 dwSize, int& nRetcode)
{
    SShmItem* pstItem = CShmMgr::Instance().GetShmItem(nKey);
    if(NULL == pstItem)
    {
        nRetcode = -1;
        return NULL;
    }

    if(dwSize != pstItem->m_dwSize)
    {
        nRetcode = 1;
        return NULL;
    }

    pstItem->m_nRef++;

    return pstItem->m_pShm;
}

EWSShmErrCode WS_CreateShm(int nKey, uint32 dwSize, void** ppShmRet)
{
    if(NULL == ppShmRet || 0 == nKey)
    {
        return WS_SHM_INVALID_PARAM;
    }

    *ppShmRet = NULL;

    if(0 == dwSize)
    {
        return WS_SHM_INVALID_PARAM;
    }

	void*pVoid      = NULL ;
	int nRetCode  = 0;

	pVoid = CheckExist(nKey, dwSize, nRetCode);
	if(NULL != pVoid)
	{
		*ppShmRet = pVoid;
		return WS_SHM_ALREADY_EXISTS;
	}

	if(1 == nRetCode)
	{
		return WS_SHM_SIZE_ERROR;
	}

    EWSShmErrCode nRet = WS_SUCCESS;
    bool bCreater   = true;

	int nHandle   = shmget((key_t)nKey, dwSize, 0666|IPC_CREAT|IPC_EXCL);
    if(-1 == nHandle)
    {
        if(EEXIST == errno)
        {
            bCreater = false;
            nRet = WS_SHM_ALREADY_EXISTS;
        }
        nHandle = shmget((key_t)nKey, dwSize, 0666|IPC_CREAT);
        if(-1 == nHandle)
        {
            if(EINVAL == errno)
            {
               return WS_SHM_SIZE_ERROR;
            }

            return WS_UNKNOWN_ERR;
        }
    }

    void* pShm = shmat(nHandle, NULL, SHM_R);
    if((void*)-1 == pShm)
    {
        return WS_UNKNOWN_ERR;
    }

    SShmItem* pstShitem = new SShmItem;
    assert(NULL != pstShitem);

    pstShitem->m_nKey       = nKey;
    pstShitem->m_nRef		= 1 ;
    pstShitem->m_pShm       = pShm;
    pstShitem->m_nHandle    = nHandle;
    pstShitem->m_dwSize     = dwSize;
    pstShitem->m_bCreat     = bCreater;

    CShmMgr::Instance().AddShmItem(pstShitem);

    *ppShmRet = pShm;

    return nRet;
}

EWSShmErrCode WS_DeleteShm(int nKey)
{
    bool  bRet  = CShmMgr::Instance().DeleteShm(nKey);
    int nSize = CShmMgr::Instance().GetItemSize();

    if(0 == nSize)
    {
        CShmMgr::Instance().Release();
    }

    if(bRet)
    {
        return WS_SUCCESS;
    }

    return WS_SHM_NOT_EXISTS;
}
