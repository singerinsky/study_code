#include "../header.h"
#include <atomic>
#include <cstring>
#include <future>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
// Path: src/test_case/test_epoll.cpp
// symbol: include
// hover info: /home/gl/workspace/study_code/src/header.h
// symbol: header
// hover info: /home/gl/workspace/study_code/src/header.h
// symbol: h
// hover info: /home/gl/works
TEST(Net_Test, test_client) {
  LOG(INFO) << "NetTest...test_client";
  while (true) {
    usleep(100000);
  }
  std::set<int> name_set;
  size_t size = name_set.size();
}

int create_virtual_fd() {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    LOG(ERROR) << ("socket");
    return 1;
  }
  int flags = fcntl(fd, F_GETFL, 0);
  if (flags == -1) {
    LOG(ERROR) << ("fcntl");
    return 1;
  }

  flags |= O_NONBLOCK;
  if (fcntl(fd, F_SETFL, flags) == -1) {
    LOG(ERROR) << ("fcntl");
    return 1;
  }
  return fd;
}

void test_switch_coroutine() {
  int epoll_fd = ::epoll_create(5);

  std::atomic_bool flag = false;
  auto call_func = [&]() {
    while (true) {
      if (flag == false) {
        usleep(1000000);
        LOG(INFO) << "sleep!";
      } else {
        int secondary_fd = create_virtual_fd();
        char *buff = new char[100];
        LOG(INFO) << "create new file decr:" << secondary_fd;
        strncpy(buff, "nice day", 8);
        struct epoll_event event;
        event.events = EPOLLIN;       // 可读事件
        event.data.fd = secondary_fd; // 第二个文件描述符
        event.data.ptr = (void *)buff;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, secondary_fd, &event) == -1) {
          LOG(ERROR) << ("epoll_ctl");
          return;
        }
        return;
      }
    }
  };

  // 创建一个异步任务，异步执行call_func函数
  auto sync = std::async(std::launch::async, call_func);
  LOG(INFO) << "start main thread!";
  epoll_event event_list[10];
  while (true) {
    int num_events = epoll_wait(epoll_fd, event_list, 10, 50);
    LOG(INFO) << "start epoll pulling! with event numbsers:" << num_events;
    if (num_events == -1) {
      LOG(ERROR) << ("epoll_wait");
    }
    flag = true;
    usleep(10000);
    for (int i = 0; i < num_events; i++) {
      if (event_list[i].data.fd == epoll_fd) {
        // 处理主要的文件描述符的读写操作
      } else {
        // 处理第二个文件描述符的读写操作
        LOG(INFO) << "manual add file descr!" << event_list[i].data.fd;
        LOG(INFO) << (char *)event_list[i].data.ptr;
      }
    }
  }
}

TEST(Net_Test, test_epoll) {
  LOG(INFO) << "NetTest...test_epoll";
  test_switch_coroutine();
}