#ifndef C31C342F_3F33_4DB8_9E59_05DF6FF7BCCF
#define C31C342F_3F33_4DB8_9E59_05DF6FF7BCCF

#include "../header.h"
#include <array>
#include <atomic>
#include <cstdint>

#ifndef unlikely
#if defined(__GNUC__) || defined(__clang__)
#define unlikely(x) __builtin_expect(!!(x), 0)
#else
#define unlikely(x) (x)
#endif
#endif /* unlikely */

template <typename T, uint32_t BufferSize = 4096> class CRingBuffer {
public:
  struct CursorInfo {
    std::atomic<uint32_t> tail;
    std::atomic<uint32_t> head;
    CursorInfo() : tail(0), head(0) {}
  };

  uint32_t GetSize() const { return m_size; }

  bool EnqueueBulk(const T *pStart, uint32_t dwCount) {
    uint32_t dwProdHead, dwProdHeadNext; // = m_oProdCursor.head;
    uint32_t dwCurrentFreeCount = 0; // = m_oConsCursor.tail;
    uint32_t dwAddCount = TryMoveProdHead(dwCount, dwProdHead, dwProdHeadNext,
                                          dwCurrentFreeCount);
    if (dwAddCount == 0) {
      LOG(INFO) << "add to queue failed! need space:" << dwCount
                << " now:" << dwCurrentFreeCount;
      return false;
    }
    _DoEnqueue(pStart, dwProdHead, dwAddCount);
    UpdateConsTail(dwProdHead, dwProdHeadNext);
    return true;
  }

  bool DequeueBulk(T *pOut, uint32_t dwOutCount) {
    uint32_t dwConsHead, dwConsNextHead, dwCurrentCount;
    uint32_t dwDequeuCount =
        TryMoveConsHead(dwConsHead, dwConsNextHead, dwCurrentCount, dwOutCount);
    if (dwDequeuCount == 0) {
      return false;
    }

    return false;
  }

  void DumpQueue(bool bDumpContent = false) {
    std::stringstream str;
    str << "Producer tail:" << m_oProdCursor.tail.load()
        << " head:" << m_oProdCursor.head.load()
        << " Consumer tail:" << m_oConsCursor.tail.load()
        << " head:" << m_oConsCursor.head.load() << " buffer:";

    if (bDumpContent) {
      for (uint32_t i = 0; i < BufferSize; i++) {
        str << m_buffer[i] << " ";
      }
    }

    LOG(INFO) << "dump info:" << str.str();
  }

protected:
  uint32_t TryMoveProdHead(uint32_t dwCount, uint32_t &dwProdHeadOut,
                           uint32_t &dwProdHeadNextOut,
                           uint32_t &dwCurrentFreeCount) {
    bool success = false;
    do {
      dwProdHeadOut = m_oProdCursor.head.load();
      uint32_t dwConsTail = m_oConsCursor.tail.load();

      dwCurrentFreeCount = BufferSize + dwConsTail - dwProdHeadOut;

      if (dwCurrentFreeCount < dwCount) {
        return 0;
      }
      dwProdHeadNextOut = dwProdHeadOut + dwCount;

      // 单个生产者的话
      if (m_bSP) {
        m_oProdCursor.head.store(dwProdHeadNextOut);
        success = true;
      } else {
        // 多个生产者
        success = m_oProdCursor.head.compare_exchange_weak(dwProdHeadOut,
                                                           dwProdHeadNextOut);
      }

    } while (!success);
    return dwCount;
  }

  uint32_t TryMoveConsHead(uint32_t &dwOldHead, uint32_t &dwNewHead,
                           uint32_t &dwCurrentCount, uint32_t dwCountNeeded) {
    bool success;
    do {
      dwOldHead = m_oConsCursor.head.load();
      uint32_t dwProdTail = m_oProdCursor.tail.load();
      dwCurrentCount = (dwProdTail - dwOldHead);

      if (dwCountNeeded > dwCurrentCount) {
        return 0;
      }

      dwNewHead = dwOldHead + dwCountNeeded;

      if (m_bSP) {
        m_oConsCursor.head.store(dwNewHead);
        success = true;
      } else {
        m_oConsCursor.head.compare_exchange_weak(dwOldHead, dwNewHead);
        success = true;
      }
    } while (unlikely(success == false));
    return dwCountNeeded;
  }

  // head 最终是要和head相等的
  void UpdateConsTail(uint32_t dwProdOldHead, uint32_t dwProdHeadNext) {

    bool success = false;
    do {
      if (!m_bSP) {
        success = m_oProdCursor.tail.compare_exchange_weak(dwProdOldHead,
                                                           dwProdHeadNext);
        // asm volatile("pause" ::: "memory");
      } else {
        m_oProdCursor.tail.exchange(dwProdHeadNext);
        success = true;
      }

    } while (!success);
  }
  // 按照4位优化
  void _DoEnqueue(const T *pStart, uint32_t dwOldHead, uint32_t dwCount) {
    uint32_t idx = dwOldHead & m_mask;
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

  void _DoDequeue(T *pOut, uint32_t dwCount, uint32_t dwConsTail) {
    uint32_t idx = dwConsTail & m_mask;
    int incr = 0;
    if (idx + dwCount < m_size) {
      for (; incr < (dwCount & ((~(unsigned)0x3))); incr += 4, idx += 4) {
        pOut[incr] = m_buffer[idx];
        pOut[incr + 1] = m_buffer[idx + 1];
        pOut[incr + 2] = m_buffer[idx + 2];
        pOut[incr + 3] = m_buffer[idx + 3];
      }

      switch (dwCount & 0x3) {
      case 3:
        pOut[incr++] = m_buffer[idx++];
      case 2:
        pOut[incr++] = m_buffer[idx++];
      case 1:
        pOut[incr++] = m_buffer[idx++];
      }
    } else {
      for (; idx < m_size; incr++, idx++) {
        pOut[incr] = m_buffer[idx];
      }

      for (idx = 0; incr < dwCount; incr++, idx++) {
        pOut[incr] = m_buffer[idx];
      }
    }
  }

private:
  std::array<T, BufferSize> m_buffer;
  uint32_t m_size = BufferSize;
  uint32_t m_mask = BufferSize - 1;
  bool m_bSP = true; // 如果是单个生产者的话
  CursorInfo m_oConsCursor;
  CursorInfo m_oProdCursor;
};

#endif /* C31C342F_3F33_4DB8_9E59_05DF6FF7BCCF */
