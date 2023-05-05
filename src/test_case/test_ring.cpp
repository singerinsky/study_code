#include "../header.h"
#include "../util/thread_ring_buffer.h"

template class CRingBuffer<char>;

TEST(RingBufferTest, test001) {
  LOG(INFO) << "start test ringbuffertest";
  CRingBuffer<char> *buffer = new CRingBuffer<char>;

  std::thread putThread([&buffer]() {
    const char *name = "guanlei";
    for (int i = 0; i < 4096; i++) {
      bool rst = buffer->EnqueueBulk(name, 4);
      if (rst) {
        LOG(INFO) << "add success i=" << i;
      }
    }
  });

  std::thread getThread([&buffer]() {
    int successrst = 0;
    while (true) {
      char buff[64];
      memset(buffer, 0, 64);
      bool rst = buffer->DequeueBulk(buff, 4);
      if (rst) {
        successrst++;
        LOG(INFO) << "get success successrst=" << successrst;
      }
    }
  });
  // putThread.join();
  getThread.join();
  // buffer->DumpQueue();
}