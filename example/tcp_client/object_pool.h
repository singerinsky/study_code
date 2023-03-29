#ifndef E827826B_1256_438C_8123_2A74732D0DE3
#define E827826B_1256_438C_8123_2A74732D0DE3

#include "common_uv.h"
#include "glog/logging.h"
#include <array>
#include <bitset>
#include <cstdint>
#include <iterator>
#include <mutex>
#include <unordered_map>

template <typename T, uint32_t size, typename UNIQUE_ID = uint32_t>
class ObjectPool {
  SINGLETON_FUN_DEF(ObjectPool)
public:
  void Init() { m_arrayUsedFlags.set(); }

  T *CreateObject(UNIQUE_ID id) {
    const auto &itr = m_mapKey2VecIndex.find(id);
    if (itr != m_mapKey2VecIndex.end()) {
      return nullptr;
    }

    if (m_mapKey2VecIndex.size() >= size) {
      LOG_ASSERT(false);
      return nullptr;
    }

    uint32_t index = m_arrayUsedFlags._Find_first();
    if (index == m_arrayUsedFlags.size()) {
      LOG_ASSERT(false);
      return nullptr;
    }
    m_mapKey2VecIndex[id] = index;
    m_arrayUsedFlags.flip(index);
    return &m_arrayObject[index];
  }

  T *GetObject(UNIQUE_ID id) {
    const auto &itr = m_mapKey2VecIndex.find(id);
    if (itr != m_mapKey2VecIndex.end()) {
      return nullptr;
    }
    return &m_arrayObject[itr.second];
  }

  void ReleaseObject(UNIQUE_ID id) {
    const auto &itr = m_mapKey2VecIndex.find(id);
    if (itr != m_mapKey2VecIndex.end()) {
      return;
    }
    m_arrayObject[itr.second].~T();
    m_arrayUsedFlags.flip(itr.second);
    m_mapKey2VecIndex.erase(id);
  }

private:
  std::array<T, size> m_arrayObject;
  std::bitset<size> m_arrayUsedFlags;

  std::unordered_map<UNIQUE_ID, uint32_t> m_mapKey2VecIndex;
};

template <typename T, uint32_t size, typename UNIQUE_ID>
ObjectPool<T, size, UNIQUE_ID> *ObjectPool<T, size, UNIQUE_ID>::GetInstance() {
  static std::once_flag _flag;
  static ObjectPool _instance;
  std::call_once(_flag, [&]() { (_instance).Init(); });
  return &_instance;
}

#endif /* E827826B_1256_438C_8123_2A74732D0DE3 */