/*
 * @file:
 * @copyright: 2012 - 2028 ByteDance. All Rights Reserved
 * @Author: guanlei
 * @Date: 2021-10-31 17:27:52
 * @brief:
 */
#pragma once

#include "../header.h"
#include "../util/thread_pool.h"
#include "gtest/gtest.h"
#include <chrono> // seconds
#include <future> // std::promise, std::future
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <string> // std::string
#include <thread> // std::thread

bool test_thread_add() {
  ThreadSafeQueue<int> queue;
  auto p_furture = std::async(std::launch::async, [&queue]() {
    auto i = 10;
    while (i > 0) {
      printf("add %d\n", i);
      queue.push(i);
      i--;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return true;
  });

  auto c_furture = std::async(std::launch::async, [&queue]() {
    auto i = 10;
    while (i > 0) {
      auto ele = queue.waitAndPop();
      i--;
      // std::this_thread::sleep_for(std::chrono::milliseconds(5));
      printf("pop %d\n", i);
    }
    return true;
  });

  return p_furture.get() == c_furture.get();
}
class ThreadClass {
public:
  void run() {
    while (true) {
      LOG(INFO) << "running.....";
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
  }

  void init() {
    auto f = std::async(std::launch::async, [this]() {
      this->run();
      return true;
    });
    m_f = std::move(f);
  }

  std::future<bool> m_f;
};

TEST(ProducerTest, ThreadSafeTest) {
  ThreadClass object_thread;
  object_thread.init();
  LOG(INFO) << "wait for objec thread";
  std::this_thread::sleep_for(std::chrono::milliseconds(100000000));
  object_thread.m_f.get();
  LOG(INFO) << "wait for objec thread";
}

// use thread_local instead static
void test_thread_local_value() {
  //局部变量使用thread_local 默认含有static 的语义
  thread_local int count = 0;
  thread_local void *buff = malloc(1024);
  while (true) {
    count++;
    int *int_point = (int *)buff;
    *int_point = 1;
    LOG(INFO) << "thread " << std::this_thread::get_id() << " value " << count;
    ::usleep(100000);
  }
}

TEST(TestThread, test_thread_local_value) {
  std::vector<std::future<void>> pending_future;
  int i = 0;
  while (i < 10 && ++i) {
    LOG(INFO) << "launch thread";
    auto thread_ref = std::async(std::launch::async, test_thread_local_value);
    pending_future.emplace_back(std::move(thread_ref));
  }

  for (auto &itr : pending_future) {
    itr.get();
  }
}