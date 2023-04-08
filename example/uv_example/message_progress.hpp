#ifndef A7173CE9_EC9C_4048_A4E0_269786AE1712
#define A7173CE9_EC9C_4048_A4E0_269786AE1712
#include "common_uv.h"
#include "message_template.hpp"
#include <cstdint>
#include <cstring>

// 事件由logic thread->uv
enum RequestType {
  REQUEST_LISTEN = 1, // 监听事件
};
class NetServiceBase;

struct RequestBase {
  RequestType m_wType;
  RequestBase() { memset(this, 0, sizeof(RequestBase)); }
};

struct RequestListen : public RequestBase {
  RequestListen(NetServiceBase *pNetService) {
    m_wType = REQUEST_LISTEN;
    m_pNetService = pNetService;
  }
  NetServiceBase *m_pNetService;
};

// 事件由uv->logic thread
enum EventType {
  EVENT_NEW_CONNECTION = 1,   // 新连接
  EVENT_CONNECTION_CLOSE = 2, // 连接断开
  EVENT_NEW_MESSAGE = 3,      // 新的数据消息
};

struct EventBase {
  EventType m_wType;
  EventBase(EventType eType) : m_wType(eType) {}
};

struct NSNewConnectionEvent : public EventBase {
  uint32_t m_dwConnectionId;
  uint32_t m_dwServiceId;
  NSNewConnectionEvent() : EventBase(EVENT_NEW_CONNECTION) {
    m_dwConnectionId = 0;
    m_dwServiceId = 0;
  }
};

struct NSConnectionCloseEvent : public EventBase {
  uint32_t m_dwConnectionId;
  uint32_t m_dwServiceId;
  NSConnectionCloseEvent() : EventBase(EVENT_CONNECTION_CLOSE) {
    m_dwConnectionId = 0;
    m_dwServiceId = 0;
  }
};

struct NSNewMessageEvent : public EventBase {
  uint32_t m_dwConnectionId;
  uint32_t m_dwServiceId;
  MessageBase *m_pEvent;
  NSNewMessageEvent(uint32_t dwConnID, uint32_t dwServiceID,
                    MessageBase *pEvent)
      : EventBase(EVENT_CONNECTION_CLOSE) {
    m_dwConnectionId = dwConnID;
    m_dwServiceId = dwServiceID;
    m_pEvent = pEvent;
  }
};

class EventProgress {
public:
  virtual int ProgressMsg(RequestBase *pMsg) = 0;
};

#endif /* A7173CE9_EC9C_4048_A4E0_269786AE1712 */
