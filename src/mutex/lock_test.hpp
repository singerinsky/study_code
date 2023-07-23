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
  std::memcpy(&mData, &value, sizeof(T));
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
  std::memcpy(&value, &mData, sizeof(T));
  // 判断当前版本号是否与加载时的版本号相同
  return version == mVersion;
}
