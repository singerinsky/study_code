#ifndef D60C8382_21DD_45CE_B730_9CEC929247F9
#define D60C8382_21DD_45CE_B730_9CEC929247F9
#include "object_pool.h"
#include "uv.h"

struct MsgHead {
  uint32_t dwMsgID;
  uint32_t dwMsgLen;
};

class UVTcpClient {
public:
  UVTcpClient() {
    m_handle_t.data = this;
    m_connect_t.data = this;
  }
  ~UVTcpClient() {}
  void OnRecv(const char *buffMsg);
  void ConnectTo(const char *strIp, uint32_t port);
  void SendMsg();
  uv_tcp_t m_handle_t;
  uv_connect_t m_connect_t;
};

void buf_alloc(uv_handle_t *tcp, size_t size, uv_buf_t *buf);

void read_cb(uv_stream_t *tcp, ssize_t nread, const uv_buf_t *buf);

typedef ObjectPool<UVTcpClient, 10> UVTcpClienPool;

#endif /* D60C8382_21DD_45CE_B730_9CEC929247F9 */
