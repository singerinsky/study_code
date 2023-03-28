#include <cstring>
#include <glog/logging.h>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

class CircularBuffer {
public:
  CircularBuffer(uint32_t size)
      : m_buffer(new char[size]), m_size(size), m_head(0), m_tail(0) {}

  ~CircularBuffer() { delete[] m_buffer; }

  uint32_t write(const void *data, uint32_t bytes) {
    const char *p = reinterpret_cast<const char *>(data);
    uint32_t remaining = bytes;

    while (remaining > 0) {
      uint32_t capacity = getCapacity();

      if (capacity == 0) {
        return remaining;
      }

      uint32_t count = std::min(remaining, capacity);
      uint32_t end = std::min(m_head + count, m_size);

      std::memcpy(m_buffer + m_head, p, end - m_head);
      std::memcpy(m_buffer, p + (end - m_head), count - (end - m_head));

      m_head = (m_head + count) % m_size;

      p += count;
      remaining -= count;
    }
    return remaining;
  }

  uint32_t read(void *data, uint32_t bytes) {
    char *p = reinterpret_cast<char *>(data);
    uint32_t remaining = bytes;
    uint32_t tmpTail = m_tail;
    uint32_t tmpDataInbuff = getOccupancy();
    while (remaining > 0) {
      uint32_t count = std::min(remaining, tmpDataInbuff);

      if (count == 0) {
        return bytes - remaining;
      }

      uint32_t end = std::min(tmpTail + count, m_size);

      memcpy(p, m_buffer + tmpTail, end - tmpTail);
      memcpy(p + (end - tmpTail), m_buffer, count - (end - tmpTail));

      tmpTail = (tmpTail + count) % m_size;
      tmpDataInbuff -= count;
      p += count;
      remaining -= count;
    }

    return bytes - remaining;
  }

  void discard(uint32_t bytes) {
    if (bytes > getOccupancy()) {
      LOG(ERROR) << "bytes:" << bytes << " occupancy:" << getOccupancy();
      LOG_ASSERT(false);
      return;
    }
    m_tail = (m_tail + bytes) % m_size;
  }

  // 获取写入地址头部
  char *getHead() const { return m_buffer + m_head; }

  // 获取连续内存空间,用于连续写入
  uint32_t getHeadContinuouslySize() const {
    if (m_head >= m_tail) {
      return m_size - m_head;
    } else {
      return m_tail - m_head - 1;
    }
  }

  // 移动写入标志
  bool moveHead(uint32_t dwStep) {
    if (dwStep > m_size)
      return false;

    m_head = (m_head + dwStep) % m_size;
    return true;
  }

  // 获取剩余容量
  uint32_t getCapacity() {
    if (m_head >= m_tail) {
      return m_size - (m_head - m_tail) - 1;
    } else {
      return m_tail - m_head - 1;
    }
  }

  // 获取目前数据大小
  uint32_t getOccupancy() {
    if (m_head >= m_tail) {
      return m_head - m_tail;
    } else {
      return m_size - (m_tail - m_head);
    }
  }

  // uint32_t

  char *m_buffer;
  uint32_t m_size;
  uint32_t m_head; // 写入端
  uint32_t m_tail; // 读取端
};