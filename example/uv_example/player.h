#ifndef E78EF5C3_0E34_46FE_8087_36C41FF9C26D
#define E78EF5C3_0E34_46FE_8087_36C41FF9C26D
#include "../util/type_def.h"
#include "object_pool.h"

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
};

#endif /* E78EF5C3_0E34_46FE_8087_36C41FF9C26D */
