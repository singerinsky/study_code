#include "uv_server.hpp"
#include "../../header.h"
#include "uv.h"
#include <ratio>
#include <thread>

CUVServer::CUVServer() {}

CUVServer::~CUVServer() {}

CUVServer *CUVServer::get_instance() {
  static std::once_flag _flag;
  static CUVServer _instance;
  std::call_once(_flag, [&]() {
    _instance.init();
    LOG(INFO) << "do init cuvserver";
  });
  return &_instance;
}

bool CUVServer::init() {
  m_pLoopHandle = uv_loop_new();
  if (!m_pLoopHandle) {
    return false;
  }
  return true;
}

void CUVServer::pause(uint32_t ms) {
  chrono::duration<int, std::milli> tSleepTime(ms);
  this_thread::sleep_for(tSleepTime);
}

void CUVServer::start() {
  if (m_pLoopHandle) {
    int rst = 0;
    while (true) {
      rst = uv_run(m_pLoopHandle, UV_RUN_DEFAULT);
      LOG(INFO) << "running uv server,after one round,rst:" << rst;
      if (rst == 0) {
        pause(1000);
      }
    }
  }
}
