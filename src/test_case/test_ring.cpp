#include "../header.h"
#include "../util/thread_ring_buffer.h"

template class CRingBuffer<char>;

TEST(RingBufferTest, test001) {
  LOG(INFO) << "start test ringbuffertest";
  CRingBuffer<char> *buffer = new CRingBuffer<char>;
  const char *name = "guanlei";
  for (int i = 0; i < 4096; i++) {
    bool rst = buffer->EnqueueBulk(name, 4);
    // if (i % 4 == 0) {
    char buff[64];
    memset(buffer, 0, 64);
    buffer->DequeueBulk(buff, 4);
    //   // LOG(INFO) << "buffer:" << buff
    //   //         << " current size:" << buffer->GetCurrentCapacity();
    // }
    LOG(INFO) << " current size:" << buffer->GetCurrentCapacity()
              << " in iterator:" << i << " with enqueue:" << rst;
  }
  buffer->EnqueueBulk(name, 1);
  // buffer->DumpQueue();
}