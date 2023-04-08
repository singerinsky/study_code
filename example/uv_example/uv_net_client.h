#ifndef B6B49D68_0202_4D26_8DDD_A34692670831
#define B6B49D68_0202_4D26_8DDD_A34692670831
#include "circular_buffer.h"
#include "common_uv.h"
#include "message.pb.h"
#include "message_head.h"
#include "object_pool.h"
#include "uv.h"
#include <cstdint>

#define DEFAULT_BUFF_SIZE 1024 * 64

class CUvNetClient {
public:
  CUvNetClient()
      : m_oReadBuffer(DEFAULT_BUFF_SIZE), m_oSendBuffer(DEFAULT_BUFF_SIZE) {}
  CUvNetClient(uint32_t dwBuffSize)
      : m_oReadBuffer(dwBuffSize), m_oSendBuffer(dwBuffSize) {}
  CUvNetClient(uint32_t dwConID, uv_handle_t *pHandle);

  char *getBufferHeadForUVWrite() const { return m_oReadBuffer.getHead(); }

  uint32_t getBufferSizeForUVWrite() const {
    return m_oReadBuffer.getHeadContinuouslySize();
  }

  void OnNewDataRecv(uint32_t dwDataSize);

  uint32_t GetID() const { return m_dwID; }

  void SetID(uint32_t id) { m_dwID = id; }

  void SetDesc(const std::string &strDesc) { m_strDesc = strDesc; }

  const std::string GetDesc() { return m_strDesc; }

  void SetUVHandle(uv_tcp_t *phandle) { this->m_pUvTcpHandle = phandle; }

  bool CheckReadBufferMsgNeedProcess(uint32_t &dwMsgID, uint32_t &dwMsgLen);

private:
  CircularBuffer m_oReadBuffer;
  CircularBuffer m_oSendBuffer;
  uint32_t m_dwID = 0;
  std::string m_strDesc;
  uv_tcp_t *m_pUvTcpHandle = nullptr;
};

class UVClientMgr : public ObjectPool<CUvNetClient, 10> {
public:
  SINGLETON_FUN_INBODY(UVClientMgr)
};

#endif /* B6B49D68_0202_4D26_8DDD_A34692670831 */
