#include "common_uv.h"

// close uv file handle
void common_close_cb(uv_handle_t *handle) { delete handle; }

#define SEND_BUFF_SIZE 1024000
void init_tcp_connection(uv_tcp_t *client) {
  int buff_size = SEND_BUFF_SIZE;
  uv_send_buffer_size((uv_handle_t *)client, &buff_size);
  uv_recv_buffer_size((uv_handle_t *)client, &buff_size);
}