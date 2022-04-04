#pragma once
#include "../header.h"
#include <atomic>
#include <future>
#include <gtest/gtest.h>

TEST(Atom_Test, test_001) {
  std::atomic_int* ptr_int_flag = new std::atomic_int(ATOMIC_FLAG_INIT);
  std::atomic_int int_flag = ATOMIC_FLAG_INIT;
  int_flag.store(10);
  auto future1 = std::async(std::launch::async, [&]() {
    for (int i = 0; i < 100; i++) {
      int_flag++;
      LOG(INFO) <<"add thread run "<<i<<":"<< int_flag.load();
    }
    return true;
  });

  auto future2 = std::async(std::launch::async, [&]() {
    for (int i = 0; i < 100; i++) {
      int_flag--;
      LOG(INFO) <<"sub thread run "<<i<<":"<< int_flag.load();
    }
    return true;
  });
  future2.get();
  future1.get();
  ASSERT_EQ(int_flag.load(), 10);
}

TEST(Atom_Test,test_udt_class)
{
  auto rec = std::is_trivially_copyable<SampleClass>::value;
  auto rec1 = std::is_constructible<SampleClass>::value;
  LOG(INFO)<<"SampleClass is_trivially_copyable: "<<rec;
  LOG(INFO)<<"SampleClass is_constructible: "<<rec1;
}