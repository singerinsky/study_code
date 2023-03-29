#include "uv_client.hpp"
#include "message.pb.h"
#include "uv.h"

void buf_alloc(uv_handle_t *tcp, size_t size, uv_buf_t *buf) {
  static char buff[1024];
  buf->len = size;
  buf->base = buff;
}

void read_cb(uv_stream_t *tcp, ssize_t nread, const uv_buf_t *buf) {
  UVTcpClient *pClient = (UVTcpClient *)tcp->data;
}

void write_cb(uv_write_t *req, int status) {
  if (status == 0)
    LOG(INFO) << "write call back";
  else if (status == UV_ECANCELED)
    LOG(INFO) << "UV_ECANCELED";
  else
    LOG(INFO) << "ERROR !";
}

void client_connect(uv_connect_t *req, int status) {
  UVTcpClient *pClient = (UVTcpClient *)req->data;
  LOG(INFO) << "connection status:" << status;
  if (status != 0) {
    LOG(ERROR) << "connection failed!";
    return;
  }
  req->handle->data = pClient;
  uv_read_start(req->handle, buf_alloc, read_cb);

  // send message
  pClient->SendMsg();
}

void UVTcpClient::SendMsg() {
  static char buffer[1024];
  gl::user user_info;
  user_info.set_age(34);
  user_info.set_name("guanlei");
  std::string data_buffer = user_info.SerializeAsString();
  MsgHead *head = (MsgHead *)buffer;
  head->dwMsgID = 1;
  head->dwMsgLen = sizeof(MsgHead) + data_buffer.size();
  memcpy(buffer + sizeof(MsgHead), data_buffer.c_str(), data_buffer.size());
  uv_write_t *req = (uv_write_t *)malloc(sizeof(uv_write_t));
  uv_buf_t buf_struct;
  buf_struct.base = buffer;
  buf_struct.len = head->dwMsgLen;
  uv_write(req, m_connect_t.handle, &buf_struct, 1, write_cb);
}

void UVTcpClient::ConnectTo(const char *strIp, uint32_t port) {
  struct sockaddr_in server_addr;
  uv_ip4_addr(strIp, port, &server_addr);
  uv_tcp_init(uv_default_loop(), &m_handle_t);
  int r = uv_tcp_connect(&m_connect_t, &m_handle_t,
                         (const struct sockaddr *)&server_addr, client_connect);
}

void UVTcpClient::OnRecv(const char *buffMsg) {}
