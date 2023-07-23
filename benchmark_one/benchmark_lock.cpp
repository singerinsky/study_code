#include "../header.h"
#include "../src/mutex/lock_test.hpp"
#include "../util/class_sample.h"
#include <benchmark/benchmark.h>
#include <cstdint>
#include <mutex>

void function_test_seq_lock(benchmark::State &state) {
  for (auto _ : state) {
    SeqLock<PodSampleClass> res_with_lock;

    std::thread write_thread([&]() {
      PodSampleClass object;
      int dwCountDown = 10000;
      while (dwCountDown-- > 0) {
        { res_with_lock.Store(object); }
      }
    });
    std::thread read_thread([&]() {
      PodSampleClass object;
      uint32_t dwFailCount = 0;
      uint32_t dwWinCount = 0;
      int dwCountDown = 10000;
      while (dwCountDown-- > 0) {
        {
          bool rst = res_with_lock.Load(object);
          if (rst == false) {
            dwFailCount++;
          } else {
            dwWinCount++;
          }
        }
      }
    });
    write_thread.join();
    read_thread.join();
  }
}
BENCHMARK(function_test_seq_lock);

void function_test_mutex_lock(benchmark::State &state) {
  for (auto _ : state) {

    PodSampleClass objectToProtected;
    std::mutex mutex;
    std::thread write_thread([&]() {
      PodSampleClass object;
      int dwCountDown = 10000;
      while (dwCountDown-- > 0) {
        mutex.lock();
        memcpy((void *)&objectToProtected, (void *)&object,
               sizeof(PodSampleClass));
        mutex.unlock();
      }
    });
    std::thread read_thread([&]() {
      PodSampleClass object;
      uint32_t dwFailCount = 0;
      uint32_t dwWinCount = 0;
      int dwCountDown = 10000;
      while (dwCountDown-- > 0) {
        {
          mutex.lock();
          memcpy((void *)&object, (void *)&objectToProtected,
                 sizeof(PodSampleClass));
          mutex.unlock();
        }
      }
    });
    write_thread.join();
    read_thread.join();
  }
}
BENCHMARK(function_test_mutex_lock);