#include "../header.h"
#include "../util/thread_ring_buffer.h"

template class CRingBuffer<char>;

TEST(RingBufferTest, test001) {
  LOG(INFO) << "start test ringbuffertest";
  CRingBuffer<char> *buffer = new CRingBuffer<char>;
  const char *name = "guanlei";
  for (int i = 0; i < 1024; i++) {
    buffer->EnqueueBulk(name, 4);
  }
  buffer->EnqueueBulk(name, 1);
  buffer->DumpQueue();
}