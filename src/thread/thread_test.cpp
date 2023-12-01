#include "../header.h"
#include <atomic>
#include <unistd.h>

TEST(ThreadTest, Test001) {
  // int iCount = 0;
  std::atomic<int> iIndex(0);
  std::atomic_int iCount(1);
  LOG(INFO) << "start thread test!";

  std::thread thread3([&]() {
    while (true) {
      int nStart = 3;
      if (iCount.compare_exchange_strong(nStart, 1)) {
        LOG(INFO) << "thread3:" << nStart << " index:" << iIndex.fetch_add(1);
        // iCount.store(1);
      } else {
        ::usleep(1);
      }
      //::usleep(100000);
    }
  });

  std::thread thread4([&]() {
    while (true) {
      int nStart = 3;
      if (iCount.compare_exchange_strong(nStart, 1)) {
        LOG(INFO) << "thread4:" << nStart << " index:" << iIndex.fetch_add(1);
        // iCount.store(1);
      } else {
        ::usleep(1);
      }
      //::usleep(100000);
    }
  });

  std::thread thread1([&]() {
    while (true) {
      int nStart = 1;
      if (iCount.compare_exchange_strong(nStart, 2)) {
        LOG(INFO) << "thread1:" << nStart << " index:" << iIndex.fetch_add(1);
        // iCount.store(1);
      } else {
        ::usleep(1);
      }
      //::usleep(100000);
    }
  });

  std::thread thread2([&]() {
    while (true) {
      int nStart = 2;
      if (iCount.compare_exchange_strong(nStart, 3)) {
        LOG(INFO) << "thread2:" << nStart << " index:" << iIndex.fetch_add(1);
        // iCount.store(1);
      } else {
        ::usleep(1);
      }
      //::usleep(100000);
    }
  });
  // thread1.join();
  // thread2.join();
  // thread3.join();
  sleep(1);
}

TEST(ThreadTest, Test002) {
  // int iCount = 0;
  std::atomic<int> iIndex(0);
  std::atomic_int iCount(2);
  LOG(INFO) << "start thread test!";
  int nStart = 2;
  iCount.compare_exchange_strong(nStart, 3);
  LOG(INFO) << "nStart:" << nStart;
}