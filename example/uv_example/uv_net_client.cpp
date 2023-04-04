#include "uv_net_client.h"
#include "message_template.hpp"
#include <cstdint>

bool CUvNetClient::CheckReadBufferMsgNeedProcess(uint32_t &dwMsgID,
                                                 uint32_t &dwMsgLen) {
  char buff[MSG_HEAD_SIZE];
  uint32_t dwReadSize = m_oReadBuffer.read(buff, MSG_HEAD_SIZE);
  if (dwReadSize < MSG_HEAD_SIZE) {
    LOG(INFO) << "data not ready,size is " << dwReadSize;
    return false;
  }
  uint32_t msg_id = ((MsgHead *)(buff))->dwMsgID;
  uint32_t msg_len = ((MsgHead *)(buff))->dwMsgLen;
  uint32_t data_size_in_buff = m_oReadBuffer.getOccupancy();
  if (data_size_in_buff < msg_len) {
    return false;
  }
  LOG(INFO) << "data in buffer" << buff;
  m_oReadBuffer.discard(dwReadSize);
  return true;
}

void CUvNetClient::OnNewDataRecv(uint32_t dwDataSize) {
  if (!m_oReadBuffer.moveHead(dwDataSize)) {
    LOG(ERROR) << "error of data size";
  }

  uint32_t dwMsgID, dwMsgLen;
  while (CheckReadBufferMsgNeedProcess(dwMsgID, dwMsgLen)) {
    char *_buffer = new char[dwMsgLen];
    m_oReadBuffer.read(_buffer, dwMsgLen);

    MessageBase *message = AllocNewMessage(dwMsgID);
    message->ParseFromArray(dwMsgID, _buffer, dwMsgLen);

    MessageBase *temp = AllocNewMessage(dwMsgID);
    bool bParse = temp->ParseFromArray(dwMsgID, _buffer, dwMsgLen);

    //     gl::user userinfo;
    // userinfo.ParseFromArray(_buffer, data_size_in_buff);
    // LOG(INFO) << userinfo.ShortDebugString();
  }
}