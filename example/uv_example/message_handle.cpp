#include "message_handle.h"
#include "message_progress.hpp"

uint32_t CMessageHandleMgr::ProcessMsgHandler(const EventBase *pEventBase) {
  if (pEventBase->m_wType == EVENT_NEW_CONNECTION) {
    OnNewConnection(reinterpret_cast<const NSNewConnectionEvent *>(pEventBase));
  } else if (pEventBase->m_wType == EVENT_CONNECTION_CLOSE) {

  } else if (pEventBase->m_wType == EVENT_NEW_MESSAGE) {

  } else {
    LOG(ERROR) << " unkown message type:" << pEventBase->m_wType;
    return 1;
  }
  return 0;
}

DWORD CMessageHandleMgr::OnNewConnection(const NSNewConnectionEvent *pEvent) {
  LOG(INFO) << " On New Connection Coming!!" << pEvent->m_dwConnectionId;
  return 1;
}

uint32_t
CMessageHandleMgr::ProcessClientMsgHandler(const NSNewMessageEvent *pEvent) {

  return 1;
}