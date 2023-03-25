#ifndef E4FA39DF_8C7A_41A5_8D38_81CC9D7F5A01
#define E4FA39DF_8C7A_41A5_8D38_81CC9D7F5A01
#include "net_service.h"
#include <cstdint>

class TcpNetService : public NetServiceBase {
public:
  TcpNetService(uint32_t dwId, const std::string strName)
      : NetServiceBase(dwId, strName) {}
  bool Start();
  bool Stop();
};

#endif /* E4FA39DF_8C7A_41A5_8D38_81CC9D7F5A01 */
