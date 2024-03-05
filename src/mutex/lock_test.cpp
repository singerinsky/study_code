#include "lock_test.hpp"
#include "../util/class_sample.h"

TEST(LockTest, SeqLock) {
  SeqLock<PodSampleClass> lock;
  PodSampleClass object_one = {1, 2};
  lock.Store(object_one);
  LOG(INFO) << "lock.GetVersion()=" << lock.GetVersion();
}

TEST(LockTest, RWLock) {
  RWLock rwlock;
  int t = 10;
  std::thread reader1([&]() {
    rwlock.readLock();
    std::cout << "Reader 1 is reading" << t << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    rwlock.readUnlock();
  });

  std::thread reader2([&]() {
    int count = 0;
    while ((count++) < 100) {
      rwlock.readLock();
      std::cout << "Reader 2 is reading" << t << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      rwlock.readUnlock();
    }
  });

  std::thread writer([&]() {
    rwlock.writeLock();
    t++;
    std::cout << "Writer is writing" << t << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    rwlock.writeUnlock();
  });

  reader1.join();
  reader2.join();
  writer.join();
}