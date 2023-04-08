#ifndef E78EF5C3_0E34_46FE_8087_36C41FF9C26D
#define E78EF5C3_0E34_46FE_8087_36C41FF9C26D
#include "../util/type_def.h"
#include "object_pool.h"
#include <cstdint>
#include <unordered_map>

class CPlayer {
public:
  CPlayer() = default;
  ~CPlayer() = default;

  DWORD GetID() const { return m_dwID; }
  void SetID(DWORD dwID) { m_dwID = dwID; }

private:
  DWORD m_dwID;
  std::string m_strName = "";
};

class CPlayerMgr : public ObjectPool<CPlayer, 100> {
public:
  CPlayer *GetPlayerByName(const std::string &name);

  void MapConnIDPlayerID(DWORD dwConnID, DWORD dwPlayerID);

  DWORD GetPlayerIDByConnID(DWORD dwConnID);

  static CPlayerMgr *GetInstance();

protected:
  std::unordered_map<uint32_t, uint32_t> m_mapConnID2PlayerID;
};
SINGLETON_FUN_BODY(CPlayerMgr)

#define PLAYERMGR_INSTANCE CPlayerMgr::GetInstance()

#endif /* E78EF5C3_0E34_46FE_8087_36C41FF9C26D */
