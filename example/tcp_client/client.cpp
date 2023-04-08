#include "uv.h"
#include "uv_client.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <utility>
using namespace std::chrono_literals;
static int id = 1;

std::unordered_map<uint32_t, UVTcpClient *> user_map;
static int incr_id = 1;
uv_timer_t *g_repeat_timer;

void client_timer_func(uv_timer_t *handle) {
  LOG(INFO) << "timer call function";
  for (auto itr : user_map) {
    itr.second->SendMsg();
  }
}

void init_timer_loop() {
  g_repeat_timer = new uv_timer_t();

  auto r = uv_timer_init(uv_default_loop(), g_repeat_timer);

  uv_timer_start(g_repeat_timer, client_timer_func, 0, 1000);
}

int main() {

  UVTcpClient *pClient = UVTcpClienPool::GetInstance()->CreateObject(id++);
  pClient->SetID(id);
  pClient->ConnectTo("127.0.0.1", 9090);

  init_timer_loop();
  while (true) {
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    // std::this_thread::sleep_for(100ms);
  }

  return 1;
}