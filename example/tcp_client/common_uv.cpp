#include "common_uv.h"

// close uv file handle
void common_close_cb(uv_handle_t *handle) { delete handle; }

#define SEND_BUFF_SIZE 1024000
