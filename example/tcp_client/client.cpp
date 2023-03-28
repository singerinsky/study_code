#include "uv.h"
#include "uv_client.hpp"
#include <chrono>
#include <iostream>
#include <thread>
using namespace std::chrono_literals;
static int id = 1;
int main() {

  UVTcpClient *pClient = UVTcpClienPool::GetInstance()->CreateObject(id++);
  pClient->ConnectTo("127.0.0.1", 9090);
  while (true) {
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    std::this_thread::sleep_for(100ms);
  }

  return 1;
}