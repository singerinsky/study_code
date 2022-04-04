/*
 * @file: 
 * @copyright: 2012 - 2028 ByteDance. All Rights Reserved
 * @Author: guanlei
 * @Date: 2021-11-08 17:10:11
 * @brief: 
 */
#ifndef _H_SHMMGR_H_
#define _H_SHMMGR_H_

#include <map>

#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <memory>

#include "header.h"

enum EWSShmErrCode
{
    WS_SUCCESS  = 0,
    WS_UNKNOWN_ERR              = 1,        // 未知错误
    WS_SYSTEM_ERROR             = 2,        // 系统错误
    WS_WRONG_PARAM              = 4,        // 参数错误

    WS_SHM_INVALID_PARAM        = 5,      // 共享内存参数错误
    WS_SHM_ALREADY_EXISTS       = 6,      // 共享内存已经生成
    WS_SHM_SIZE_ERROR           = 7,      // 共享内存大小问题
    WS_SHM_NOT_EXISTS           = 8,      // 共享内存不存在
};

struct SShmItem
{
    SShmItem()
    {
        m_nHandle   = 0;
        m_pShm      = NULL;
        m_nRef      = 0;
        m_nKey      = 0;
        m_dwSize    = 0;
        m_bCreat  = false;
    }
	int     m_nHandle;
    void*   m_pShm;
    int     m_nRef;
    int     m_nKey;
    uint32  m_dwSize;
    bool    m_bCreat;
};

typedef std::map<int, SShmItem*>  CShmMap;

class CShmMgr
{
    CShmMgr();
    virtual ~CShmMgr();

public:
    static CShmMgr&  Instance(){
        static CShmMgr instance;
        return instance;
    }
    
    SShmItem* GetShmItem(int nKey);
    bool AddShmItem(SShmItem* pstShmitem);
    bool DeleteShm(int nKey);
    int GetItemSize();
    void Release();

protected:
   
    CShmMap              m_oShmHandle;
};

void* CheckExist(int nKey, uint32 dwSize, int& nRetcode);

EWSShmErrCode WS_CreateShm(int nKey, uint32 dwSize, void** ppShmRet);

EWSShmErrCode WS_DeleteShm(int nKey);

#endif //_H_SHMMGR_H_
