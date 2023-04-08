#include "player.h"

void CPlayerMgr::MapConnIDPlayerID(DWORD dwConnID, DWORD dwPlayerID) {
  m_mapConnID2PlayerID[dwConnID] = dwPlayerID;
}

DWORD CPlayerMgr::GetPlayerIDByConnID(DWORD dwConnID) {
  auto itr = m_mapConnID2PlayerID.find(dwConnID);
  if (itr == m_mapConnID2PlayerID.end()) {
    return 0;
  }
  return itr->second;
}

CPlayer *CPlayerMgr::GetPlayerByName(const std::string &name) {
  return nullptr;
}