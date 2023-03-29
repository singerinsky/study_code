#include "common_uv.h"
#include "uv_net_client.h"
#include <glog/logging.h>
// close uv file handle
void common_close_cb(uv_handle_t *handle) { delete handle; }

#define SEND_BUFF_SIZE 1024000
void init_tcp_connection(uv_tcp_t *client) {
  int buff_size = SEND_BUFF_SIZE;
  uv_send_buffer_size((uv_handle_t *)client, &buff_size);
  uv_recv_buffer_size((uv_handle_t *)client, &buff_size);
  CUvNetClient *pNetClient =
      NetClientPool::GetInstance()->CreateObject(client->u.fd);
  LOG(INFO) << "create CUvNetClient id:" << client->u.fd;
  if (pNetClient == nullptr) {
    LOG(ERROR) << "create object failed! null ptr!";
    LOG_ASSERT(false);
  }
  client->data = pNetClient;
  // TODO 创建对象
  // client->data
}