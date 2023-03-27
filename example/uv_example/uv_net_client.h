#ifndef B6B49D68_0202_4D26_8DDD_A34692670831
#define B6B49D68_0202_4D26_8DDD_A34692670831
#include "circular_buffer.h"
#include "common_uv.h"
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

  void parseReadBuffer() {
    char buff[1024];
    m_oReadBuffer.read(buff, 100);
    LOG(INFO) << "data in buffer" << buff;
  }

private:
  CircularBuffer m_oReadBuffer;
  CircularBuffer m_oSendBuffer;
};

typedef ObjectPool<CUvNetClient, 10> NetClientPool;

#endif /* B6B49D68_0202_4D26_8DDD_A34692670831 */
