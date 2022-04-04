/*
 * @file: 
 * @copyright: 2012 - 2028 ByteDance. All Rights Reserved
 * @Author: guanlei
 * @Date: 2021-11-08 16:41:32
 * @brief: 
 */
#ifndef _H_WSSTACKRECORDER_H
#define _H_WSSTACKRECORDER_H

#include "header.h"
#include <string.h>
#include "shmmgr.h"

#define WS_CALLSTACK_LEN    100
#define WS_RECORD_BUF_LEN   1024


class CWSStackRecorder
{
private:
    CWSStackRecorder();
    virtual ~CWSStackRecorder();

public:

    static CWSStackRecorder& Instance(){
        static CWSStackRecorder recoder_;
        return recoder_;
    }
    struct SCallQueue
    {
        uint32  m_dwTop;
        uint64  m_adwStack[WS_CALLSTACK_LEN];

        inline void Push(uint64 dwEIP)
        {
            if(m_dwTop < WS_CALLSTACK_LEN)
            {
                m_adwStack[m_dwTop] = dwEIP;
            }
            ++m_dwTop;

        }
        inline void Pop()
        {
            if(m_dwTop > 0)
            {
                --m_dwTop;
            }
        }
    };

    bool Init(int nShmKey, const char* pszDumpFileName, 
        bool bDumpPrevInstance = true);
    void Uninit();
    
    void SetContent(const char* pcContent, uint32 dwSize)
    {
        if(nullptr == pcContent)
        {
            return;
        }
        if(dwSize > WS_RECORD_BUF_LEN)
        {
            dwSize = WS_RECORD_BUF_LEN;
        }
        memcpy(m_pcContentBuf, pcContent, dwSize);
    }

    static SCallQueue*      sm_pstQueue;

protected:
    bool _SaveToFile();

protected:
    int                     m_nShmKey;
    void*                   m_pShm;
    char*                   m_pcContentBuf;

    std::string             m_strDumpFileName;
};

class CWSFuncTracer
{
public:
    explicit CWSFuncTracer(uint32 dwEIP)
    {
        CWSStackRecorder::sm_pstQueue->Push(dwEIP);
    }
    ~CWSFuncTracer()
    {
        CWSStackRecorder::sm_pstQueue->Pop();
    }
};

//如果C++标准大于17
#if __cplusplus < 201703L
#define __WS_STACK_TRACK_ENQUEUE(line) \
	register unsigned long long __StackTrack_qwEIP;\
	__asm__("call get_eip" #line); \
	__asm__("get_eip" #line ":"); \
	__asm__("popq %0" : "=r"(__StackTrack_qwEIP)); \
	CWSFuncTracer __stacktrace_oTracer(__StackTrack_qwEIP);
#else
    #define __WS_STACK_TRACK_ENQUEUE(line)
#endif

#define _WS_STACK_TRACK_ENQUEUE(line) __WS_STACK_TRACK_ENQUEUE(line)
#define WS_STACK_TRACK_ENQUEUE _WS_STACK_TRACK_ENQUEUE(__LINE__)

EWSShmErrCode WS_GetStackRecorder(int nShmKey, const char* pszDumpFileName, 
    bool bDumpPrevInstance = true);

#endif  // _H_WMSTACKRECORDER_H
