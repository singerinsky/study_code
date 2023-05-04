#ifndef C31C342F_3F33_4DB8_9E59_05DF6FF7BCCF
#define C31C342F_3F33_4DB8_9E59_05DF6FF7BCCF

#include "../header.h"
#include <array>
#include <atomic>
#include <cstdint>

template <typename T, uint32_t BufferSize = 4096> class CRingBuffer {
public:
  struct CursorInfo {
    std::atomic<uint32_t> tail;
    std::atomic<uint32_t> head;
  };

  uint32_t GetSize() const { return m_size; }

  bool EnqueueBulk(const T *pStart, uint32_t dwCount) {
    uint32_t dwProdHead;             // = m_oProdCursor.head;
    uint32_t dwCurrentFreeCount = 0; // = m_oConsCursor.tail;
    uint32_t dwAddCount =
        TryMoveProdHead(dwCount, dwProdHead, dwCurrentFreeCount);
    if (dwAddCount == 0) {
      LOG(INFO) << "add to queue failed! need space:" << dwCount
                << " now:" << dwCurrentFreeCount;
      return false;
    }
    _DoEnqueue(pStart, dwAddCount);
    UpdateConsTail();
  }

  bool DequeueBulk(T *pOut, uint32_t dwOutCount) { return false; }

protected:
  uint32_t TryMoveProdHead(uint32_t dwCount, uint32_t &dwProdHeadOut,
                           uint32_t &dwCurrentFreeCount) {
    bool success = false;
    do {
      uint32_t dwProdHead = m_oProdCursor.head;
      uint32_t dwConsTail = m_oConsCursor.tail;

      dwCurrentFreeCount = BufferSize + dwConsTail - dwProdHead;

      if (dwCurrentFreeCount < dwCount) {
        return 0;
      }
      dwProdHeadOut = dwProdHead + dwCount;

      // 单个生产者的话
      if (m_bSP) {
        m_oProdCursor.head = dwProdHeadOut;
        success = true;
      } else {
        // 多个生产者
        success =
            m_oProdCursor.head.compare_exchange_weak(dwProdHead, dwProdHeadOut);
      }

    } while (!success);
    return dwCount;
  }

  void UpdateConsTail();
  // 按照4位优化
  void _DoEnqueue(const T *pStart, uint32_t dwCount) {
    uint32_t idx = m_oProdCursor.head & m_mask;
    int incr = 0;
    if (idx + dwCount < m_size) {
      for (; incr < (dwCount & ((~(unsigned)0x3))); incr += 4, idx += 4) {
        m_buffer[idx] = pStart[incr];
        m_buffer[idx + 1] = pStart[incr + 1];
        m_buffer[idx + 2] = pStart[incr + 2];
        m_buffer[idx + 3] = pStart[incr + 3];
      }

      switch (dwCount & 0x3) {
      case 3:
        m_buffer[idx++] = pStart[incr++];
      case 2:
        m_buffer[idx++] = pStart[incr++];
      case 1:
        m_buffer[idx++] = pStart[incr++];
      }
    } else {
      for (; idx < m_size; incr++, idx++) {
        m_buffer[idx] = pStart[incr];
      }

      for (idx = 0; incr < dwCount; incr++, idx++) {
        m_buffer[idx] = pStart[incr];
      }
    }
  }

  std::array<T, BufferSize> m_buffer;
  uint32_t m_size = BufferSize;
  uint32_t m_mask = BufferSize - 1;
  bool m_bSP = true; // 如果是单个生产者的话
  CursorInfo m_oConsCursor;
  CursorInfo m_oProdCursor;
};

#endif /* C31C342F_3F33_4DB8_9E59_05DF6FF7BCCF */
