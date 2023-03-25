#include "tcp_net_server.hpp"
#include <glog/logging.h>

bool TcpNetService::Start() {
  LOG(INFO) << "start tcp net server!";
  return true;
}

bool TcpNetService::Stop() {
  LOG(INFO) << "stop tcp net server!";
  delete this;
  return true;
}