#ifndef DC621F0F_C36D_40A5_80F4_DBB1B865E373
#define DC621F0F_C36D_40A5_80F4_DBB1B865E373

#include <cstdint>
#include <string>
#include <unordered_map>
class EventProgress;

class NetServiceBase {
public:
  NetServiceBase(uint32_t m_dwServiceID, const std::string m_strServiceName)
      : m_dwServiceID(m_dwServiceID), m_strServiceName(m_strServiceName) {}
  NetServiceBase(const NetServiceBase &) = default;
  NetServiceBase(NetServiceBase &&) = default;
  NetServiceBase &operator=(const NetServiceBase &) = default;
  NetServiceBase &operator=(NetServiceBase &&) = default;

  virtual ~NetServiceBase() {}

  virtual bool Start() = 0;
  virtual bool Stop() = 0;
  virtual bool Init(const char *str_ip, uint32_t port) {
    m_strIP = str_ip;
    m_dwPort = port;
    return true;
  }
  virtual void SetMessageProgress(EventProgress *pProgress) {
    m_pEventProgress = pProgress;
  }

  const char *GetIPString() { return this->m_strIP.c_str(); }

  uint32_t GetPort() { return this->m_dwPort; }

  uint32_t GetServiceID() { return m_dwServiceID; }

  void OnAcceptNewConnection();

protected:
  EventProgress *m_pEventProgress;
  std::string m_strIP;
  uint32_t m_dwPort;
  uint32_t m_dwServiceID;
  std::string m_strServiceName;
  // std::unordered_map<, typename Tp>
};

#endif /* DC621F0F_C36D_40A5_80F4_DBB1B865E373 */
