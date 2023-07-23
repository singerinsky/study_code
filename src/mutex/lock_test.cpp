#include "lock_test.hpp"
#include "../util/class_sample.h"

TEST(LockTest, SeqLock) {
  SeqLock<PodSampleClass> lock;
  PodSampleClass object_one = {1, 2};
  lock.Store(object_one);
  LOG(INFO) << "lock.GetVersion()=" << lock.GetVersion();
}