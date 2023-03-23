#ifndef _UV_SERVER_H_
#define _UV_SERVER_H_

#include "../../header.h"
#include "uv.h"

class CUVServer {
public:
  CUVServer();

  ~CUVServer();

  bool init();

  void start();

  void pause(uint32_t ms);

  static CUVServer *get_instance();

private:
  uv_loop_t *m_pLoopHandle = nullptr;
};
#endif