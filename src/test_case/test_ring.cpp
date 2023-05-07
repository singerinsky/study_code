#include "../header.h"
#include "../util/thread_ring_buffer.h"

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