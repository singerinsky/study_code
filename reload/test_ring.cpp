#include "../header.h"
#include "../util/thread_ring_buffer.h"
#include <unistd.h>

template class CRingBuffer<char, 1024>;

TEST(RingBufferTest, test001) {
  LOG(INFO) << "start test ringbuffertest";
  CRingBuffer<char> *buffer = new CRingBuffer<char>;

  std::thread putThreadOne([&buffer]() {
    const char *name = "guanlei";
    for (int i = 0; i < 2048; i++) {
      bool rst = buffer->EnqueueBulk(name, 4);
      if (rst) {
        LOG(INFO) << "one add success i=" << i;
      } else {
        i = i - 1;
      }
    }
  });

  std::thread putThreadTwo([&buffer]() {
    const char *name = "guanlei";
    for (int i = 0; i < 2048; i++) {
      bool rst = buffer->EnqueueBulk(name, 4);
      if (rst) {
        LOG(INFO) << "two add success i=" << i;
      } else {
        i = i - 1;
      }
    }
  });

  std::atomic<int> get_count(0);
  std::thread getThread([&buffer, &get_count]() {
    int successrst = 0;
    while (true) {
      char buff[64];
      memset(buffer, 0, 64);
      bool rst = buffer->DequeueBulk(buff, 4);
      if (rst) {
        successrst++;
        // LOG(INFO) << "get success successrst=" << successrst;
        get_count.fetch_add(1);
      } else {
        LOG(INFO) << "one current get count=" << get_count.load();
      }
    }
  });
  std::thread getThreadTwo([&buffer, &get_count]() {
    int successrst = 0;
    while (true) {
      char buff[64];
      memset(buffer, 0, 64);
      bool rst = buffer->DequeueBulk(buff, 4);
      if (rst) {
        successrst++;
        // LOG(INFO) << "get success successrst=" << successrst;
        get_count.fetch_add(1);
      } else {
        LOG(INFO) << "two current get count=" << get_count.load();
      }
    }
  });

  putThreadOne.join();
  putThreadTwo.join();
  getThread.join();
  getThreadTwo.join();
  // buffer->DumpQueue();
}
void busyWait(long long count) {
  for (long long i = 0; i < count; i++) {
    asm volatile("pause;" ::: "memory");
  }
}
TEST(RingBufferTest, test002) {
  typedef std::chrono::high_resolution_clock clock;
  typedef std::chrono::microseconds microseconds;

  const long long total = 100000000;
  LOG(INFO) << "start";
  clock::time_point start = clock::now();
  busyWait(total);
  clock::time_point end = clock::now();
  std::cout << "Execution time: "
            << std::chrono::duration_cast<microseconds>(end - start).count() /
                   1000
            << " ms" << std::endl;
  LOG(INFO) << "end";
}
#include <math.h>
void cpuIntensiveFunction() {
  for (int i = 0; i < 1000; i++) {
    // 做一些 CPU 密集型的计算
    int result = std::pow(i, 2) * std::sqrt(i);
    result /= std::log(i + 2);
  }
}

TEST(atomic_mutex, test001) {
  typedef std::chrono::high_resolution_clock clock;
  typedef std::chrono::microseconds microseconds;
  clock::time_point start = clock::now();
  std::atomic<uint32_t> a(0);
  std::thread t1([&]() {
    while (true) {
      a.fetch_add(1);
      cpuIntensiveFunction();
      usleep(1);
      if (a.load() >= 100000) {
        return;
      }
    }
  });
  std::thread t2([&]() {
    while (true) {
      a.fetch_add(1);
      cpuIntensiveFunction();
      usleep(1);
      if (a.load() >= 100000) {
        return;
      }
    }
  });

  LOG(INFO) << "atomic start";
  t1.join();
  t2.join();
  LOG(INFO) << "atomic end";
  clock::time_point end = clock::now();
  std::cout << "Execution time: "
            << std::chrono::duration_cast<microseconds>(end - start).count() /
                   1000
            << " ms" << std::endl;
}

TEST(atomic_mutex, test002) {
  typedef std::chrono::high_resolution_clock clock;
  typedef std::chrono::microseconds microseconds;
  clock::time_point start = clock::now();
  int a = 0;
  std::mutex m;
  std::thread t1([&]() {
    while (true) {
      {
        {
          std::lock_guard<std::mutex> lock(m);
          a++;
          cpuIntensiveFunction();
          usleep(1);
          if (a >= 100000) {
            return;
          }
        }
      }
    }
  });
  std::thread t2([&]() {
    while (true) {
      {
        {
          std::lock_guard<std::mutex> lock(m);
          a++;
          cpuIntensiveFunction();
          usleep(1);
          if (a >= 100000) {
            return;
          }
        }
      }
    }
  });

  LOG(INFO) << "atomic start";
  t1.join();
  t2.join();
  LOG(INFO) << "atomic end";
  clock::time_point end = clock::now();
  std::cout << "Execution time: "
            << std::chrono::duration_cast<microseconds>(end - start).count() /
                   1000
            << " ms" << std::endl;
}