#ifndef A7173CE9_EC9C_4048_A4E0_269786AE1712
#define A7173CE9_EC9C_4048_A4E0_269786AE1712
#include <cstring>
enum EventType {
  EVENT_LISTEN = 1, //监听事件

};
class NetServiceBase;

struct EventBase {
  EventType m_wType;
  EventBase() { memset(this, 0, sizeof(EventBase)); }
};

struct EventListen : public EventBase {
  EventListen(EventType eType, NetServiceBase *pNetService) {
    m_wType = eType;
    m_pNetService = pNetService;
  }
  NetServiceBase *m_pNetService;
};

class EventProgress {
public:
  virtual int ProgressMsg(EventBase *pMsg) = 0;
};

#endif /* A7173CE9_EC9C_4048_A4E0_269786AE1712 */
