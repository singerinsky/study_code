#include "common_uv.h"

void common_close_cb(uv_handle_t *handle) { delete handle; }