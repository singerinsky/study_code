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

  void parseReadBuffer() {
    char buff[MSG_HEAD_SIZE];
    uint32_t dwReadSize = m_oReadBuffer.read(buff, MSG_HEAD_SIZE);
    if (dwReadSize < MSG_HEAD_SIZE) {
      LOG(INFO) << "data not ready,size is " << dwReadSize;
      return;
    }
    uint32_t msg_id = ((MsgHead *)(buff))->dwMsgID;
    uint32_t msg_len = ((MsgHead *)(buff))->dwMsgLen;
    uint32_t data_size_in_buff = m_oReadBuffer.getOccupancy();
    if (data_size_in_buff < msg_len) {
      return;
    }
    LOG(INFO) << "data in buffer" << buff;
    m_oReadBuffer.discard(dwReadSize);
    data_size_in_buff = m_oReadBuffer.getOccupancy();
    char *_buffer = new char[data_size_in_buff];
    m_oReadBuffer.read(_buffer, data_size_in_buff);

    gl::user userinfo;
    userinfo.ParseFromArray(_buffer, data_size_in_buff);
    LOG(INFO) << userinfo.ShortDebugString();
  }

  bool moveReadBufferHead(uint32_t dwMoveStep) {
    return m_oReadBuffer.moveHead(dwMoveStep);
  }

  uint32_t GetID() const { return m_dwID; }

  void SetID(uint32_t id) { m_dwID = id; }

  void SetDesc(const std::string &strDesc) { m_strDesc = strDesc; }

  const std::string GetDesc() { return m_strDesc; }

private:
  CircularBuffer m_oReadBuffer;
  CircularBuffer m_oSendBuffer;
  uint32_t m_dwID;
  std::string m_strDesc;
};

typedef ObjectPool<CUvNetClient, 10> NetClientPool;

#endif /* B6B49D68_0202_4D26_8DDD_A34692670831 */
