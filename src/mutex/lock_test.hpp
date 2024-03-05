#include "../header.h"

// SeqLock 类模板
template <typename T> class SeqLock {
public:
  // 存储数据的方法
  void Store(const T &value);
  // 加载数据的方法
  bool Load(T &value);
  // 获取版本号的方法
  uint32_t GetVersion() const { return mVersion.load(); }

protected:
  // 数据成员
  T mData;
  std::atomic<uint32_t> mVersion = 0;
};

// 存储数据的方法
template <typename T> void SeqLock<T>::Store(const T &value) {
  // 增加版本号
  mVersion += 1;
  // 将 value 拷贝到 mData 中
  memcpy(&mData, &value, sizeof(T));
  // 增加版本号
  mVersion += 1;
}

// 加载数据的方法
template <typename T> bool SeqLock<T>::Load(T &value) {
  // 获取当前版本号
  const auto version = mVersion.load();
  // 如果版本号为奇数，表示正在更新数据，加载失败
  if ((version & 1) != 0) {
    return false;
  }
  // 将 mData 拷贝到 value 中
  memcpy(&value, &mData, sizeof(T));
  // 判断当前版本号是否与加载时的版本号相同
  return version == mVersion;
}
class RWLock {
public:
  // 读锁加锁函数
  void readLock() {
    while (true) {
      int expected = 0;
      // 判断写锁未被占用且成功将写锁设为-1时，表示获取读锁成功
      if (m_writerCount.load() == 0 &&
          m_writerCount.compare_exchange_strong(expected, -1)) {
        m_readerCount.fetch_add(1); // 读锁计数加一
        m_writerCount.store(0);     // 释放写锁
        break;                      // 退出循环
      }
      std::this_thread::sleep_for(
          std::chrono::milliseconds(10)); // 等待10毫秒后重试
    }
  }

  // 读锁解锁函数
  void readUnlock() { m_readerCount.fetch_sub(1); } // 读锁计数减一

  // 写锁加锁函数
  void writeLock() {
    int expected = 0;
    // 尝试将写锁设为1，直到成功为止
    while (!m_writerCount.compare_exchange_strong(expected, 1)) {
      std::this_thread::sleep_for(
          std::chrono::milliseconds(10)); // 等待10毫秒后重试
    }
    // 等待所有读锁释放
    while (m_readerCount.load() > 0) {
      std::this_thread::sleep_for(
          std::chrono::milliseconds(10)); // 等待10毫秒后重试
    }
  }

  // 写锁解锁函数
  void writeUnlock() { m_writerCount.store(0); } // 释放写锁

private:
  std::atomic<int> m_readerCount{0}; // 读锁计数
  std::atomic<int> m_writerCount{0}; // 写锁标志
};
