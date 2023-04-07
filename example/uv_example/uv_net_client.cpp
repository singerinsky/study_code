#include "uv_net_client.h"
#include "message_progress.hpp"
#include "message_template.hpp"
#include "uv_server.hpp"
#include <cstdint>

bool CUvNetClient::CheckReadBufferMsgNeedProcess(uint32_t &dwMsgID,
                                                 uint32_t &dwMsgLen) {
  char buff[MSG_HEAD_SIZE];
  uint32_t dwReadSize = m_oReadBuffer.read(buff, MSG_HEAD_SIZE);
  if (dwReadSize < MSG_HEAD_SIZE) {
    LOG(INFO) << "data not ready,size is " << dwReadSize;
    return false;
  }
  dwMsgID = ((MsgHead *)(buff))->dwMsgID;
  dwMsgLen = ((MsgHead *)(buff))->dwMsgLen - MSG_HEAD_SIZE;
  uint32_t data_size_in_buff = m_oReadBuffer.getOccupancy();
  if (data_size_in_buff < dwMsgLen) {
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

    // MessageBase *message = AllocNewMessage(dwMsgID);
    // message->ParseFromArray(dwMsgID, _buffer, dwMsgLen);

    MessageBase *temp = AllocNewMessage(dwMsgID);
    bool bParse = temp->ParseFromArray(dwMsgID, _buffer, dwMsgLen);
    if (bParse) {
      NSNewMessageEvent *pEvent = new NSNewMessageEvent(GetID(), 0, temp);
      if (!CUVServer::GetInstance()->push_event(pEvent)) {
        LOG(ERROR) << "error add event to queue";
      }
    } else {
      LOG(ERROR) << "parse error !";
    }
    //     gl::user userinfo;
    // userinfo.ParseFromArray(_buffer, data_size_in_buff);
    // LOG(INFO) << userinfo.ShortDebugString();
  }
}