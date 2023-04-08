#include "message_handle.h"
#include "message_progress.hpp"
#include "player.h"

uint32_t CMessageHandleMgr::ProcessMsgHandler(const EventBase *pEventBase) {
  if (pEventBase->m_wType == EVENT_NEW_CONNECTION) {
    OnNewConnection(reinterpret_cast<const NSNewConnectionEvent *>(pEventBase));
  } else if (pEventBase->m_wType == EVENT_CONNECTION_CLOSE) {
    OnConnectionClose(
        reinterpret_cast<const NSConnectionCloseEvent *>(pEventBase));
  } else if (pEventBase->m_wType == EVENT_NEW_MESSAGE) {

  } else {
    LOG(ERROR) << " unkown message type:" << pEventBase->m_wType;
    return 1;
  }
  return 0;
}

DWORD CMessageHandleMgr::OnNewConnection(const NSNewConnectionEvent *pEvent) {
  LOG(INFO) << " On New Connection Coming!!" << pEvent->m_dwConnectionId;
  CPlayer *newPlayer = PLAYERMGR_INSTANCE->CreateObject();
  PLAYERMGR_INSTANCE->MapConnIDPlayerID(pEvent->m_dwConnectionId,
                                        newPlayer->GetID());
  LOG(INFO) << "New player connection id is:" << newPlayer->GetID()
            << " connection id:" << pEvent->m_dwConnectionId;
  return 1;
}

DWORD CMessageHandleMgr::OnConnectionClose(
    const NSConnectionCloseEvent *pEvent) {
  DWORD dwPlayerID =
      PLAYERMGR_INSTANCE->GetPlayerIDByConnID(pEvent->m_dwConnectionId);
  CPlayer *pPlayer = PLAYERMGR_INSTANCE->GetObject(dwPlayerID);
  if (pPlayer == nullptr) {
    LOG(INFO) << "player not found! connection id:" << pEvent->m_dwConnectionId;
  } else {
    PLAYERMGR_INSTANCE->ReleaseObject(pEvent->m_dwConnectionId);
  }
  return 0;
}

uint32_t
CMessageHandleMgr::ProcessClientMsgHandler(const NSNewMessageEvent *pEvent) {

  return 1;
}