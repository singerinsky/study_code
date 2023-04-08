#ifndef FB8641E6_34B6_46B1_AE2B_C389274CC391
#define FB8641E6_34B6_46B1_AE2B_C389274CC391

#include "../util/type_def.h"
#include "message_progress.hpp"
#include <cstdint>

class EventBase;

class CMessageHandleMgr {
public:
  static DWORD ProcessMsgHandler(const EventBase *pEventBase);
  static DWORD ProcessClientMsgHandler(const NSNewMessageEvent *pEvent);

protected:
  static DWORD OnNewConnection(const NSNewConnectionEvent *pEvent);
};

#endif /* FB8641E6_34B6_46B1_AE2B_C389274CC391 */
