#include "../../header.h"
#include "message_progress.hpp"
#include "tcp_net_server.hpp"
#include "uv_server.hpp"
#include <cstdio>
#include <future>
#include <gflags/gflags.h>
#include <thread>

void signal_handler(int sig) {
  switch (sig) {
  case SIGHUP:
    perror("Received hangup signal.");
    break;
  case SIGTERM:
    perror("Received terminate signal.");
    exit(EXIT_SUCCESS);
    break;
  case SIGINT:
    LOG(INFO) << " get server stop signal";
    exit(EXIT_SUCCESS);
    break;
  default:
    printf("Unhandled signal %s\n", strsignal(sig));
    break;
  }
}

DEFINE_bool(daemon, false, "run daemon");
DEFINE_int32(log_level, google::INFO, "run daemon");

// glog默认定义了log_dir和log_level
// 执行  ./uv_server --log_dir=./
int main(int argc, char **argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  FLAGS_logbufsecs = 0;

  signal(SIGHUP, signal_handler);
  signal(SIGTERM, signal_handler);
  signal(SIGINT, signal_handler);
  if (FLAGS_daemon) {
    FLAGS_alsologtostderr = false;
    daemon(1, 1);
  } else {
    FLAGS_logtostderr = true;
  }

  auto thread_net = std::async(std::launch::async,
                               []() { CUVServer::get_instance()->start(); });

  TcpNetService *pService = new TcpNetService(1, "clientservice");
  pService->Init("0.0.0.0", 9090);
  RequestListen *request = new RequestListen(pService);
  CUVServer::get_instance()->push_request(request);

  while (true) {
    std::this_thread::sleep_for(100ms);
    EventBase *event;
    if (CUVServer::get_instance()->pop_event(event)) {
      LOG(INFO) << "process message from uv engine!";
    }
  }

  gflags::ShutDownCommandLineFlags();
  google::ShutdownGoogleLogging(); // 关闭日志系统

  return 1;
}