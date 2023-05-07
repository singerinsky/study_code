#include "../header.h"
#include "../util/class_sample.h"
#include "../util/thread_ring_buffer.h"
#include <algorithm>
#include <atomic>
#include <benchmark/benchmark.h>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unistd.h>
#include <unordered_map>

void function_test_mutex_and_atomic_with_atomic(benchmark::State &state) {
  for (auto _ : state) {
    std::atomic<uint32_t> a(0);
    std::thread t1([&]() {
      while (true) {
        a.fetch_add(1);
        if (a.load() >= 10000) {
          return;
        }
        // asm volatile("pause;" ::: "memory");
        // usleep(10);
      }
    });
    std::thread t2([&]() {
      while (true) {
        a.fetch_add(1);
        if (a.load() >= 10000) {
          return;
        }
        // asm volatile("pause;" ::: "memory");
        // usleep(10);
      }
    });
    std::thread t3([&]() {
      while (true) {
        a.fetch_add(1);
        if (a.load() >= 10000) {
          return;
        }
        // asm volatile("pause;" ::: "memory");
        // usleep(10);
      }
    });

    std::thread t4([&]() {
      while (true) {
        a.fetch_add(1);
        if (a.load() >= 10000) {
          return;
        }
        // asm volatile("pause;" ::: "memory");
        // usleep(10);
      }
    });
    t1.join();
    t2.join();
    t3.join();
    t4.join();
  }
}
BENCHMARK(function_test_mutex_and_atomic_with_atomic);

void function_test_mutex_and_atomic_with_mutex(benchmark::State &state) {

  for (auto _ : state) {
    volatile int a = 0;
    std::mutex m;
    std::thread t1([&]() {
      while (true) {
        {
          {
            std::lock_guard<std::mutex> lock(m);
            a++;
            // LOG(INFO) << "t1:" << a;
            if (a >= 10000) {
              return;
            }
          }
          // usleep(10);
          // asm volatile("pause;" ::: "memory");
        }
      }
    });
    std::thread t2([&]() {
      while (true) {
        {
          {
            std::lock_guard<std::mutex> lock(m);
            a++;
            // LOG(INFO) << "t2:" << a;
            if (a >= 10000) {
              return;
            }
          }
          // usleep(10);
          // asm volatile("pause;" ::: "memory");
        }
      }
    });
    std::thread t3([&]() {
      while (true) {
        {
          {
            std::lock_guard<std::mutex> lock(m);
            a++;
            // LOG(INFO) << "t2:" << a;
            if (a >= 10000) {
              return;
            }
          }
          // usleep(10);
          // asm volatile("pause;" ::: "memory");
        }
      }
    });
    std::thread t4([&]() {
      while (true) {
        {
          {
            std::lock_guard<std::mutex> lock(m);
            a++;
            // LOG(INFO) << "t2:" << a;
            if (a >= 10000) {
              return;
            }
          }
          // usleep(10);
          // asm volatile("pause;" ::: "memory");
        }
      }
    });
    t1.join();
    t2.join();
    t3.join();
    t4.join();
  }
}
BENCHMARK(function_test_mutex_and_atomic_with_mutex);