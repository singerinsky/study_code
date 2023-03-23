#include "../../header.h"
#include "uv_server.hpp"
#include <cstdio>
#include <gflags/gflags.h>

void signal_handler(int sig) {
  switch (sig) {
  case SIGHUP:
    perror("Received hangup signal.");
    break;
  case SIGTERM:
    perror("Received terminate signal.");
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
  google::InitGoogleLogging("us");
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  signal(SIGHUP, signal_handler);
  signal(SIGTERM, signal_handler);
  if (FLAGS_daemon) {
    FLAGS_alsologtostderr = false;
    daemon(1, 1);
  }
  CUVServer::get_instance()->start();
  gflags::ShutDownCommandLineFlags();
  google::ShutdownGoogleLogging(); // 关闭日志系统
  return 1;
}