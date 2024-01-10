#ifndef FB614393_1C69_4704_9AB7_B14334DABAA7
#define FB614393_1C69_4704_9AB7_B14334DABAA7
#include "algorithm_double_linklist.h"
#include <unordered_map>
template <class T, class V> class LRUCache {
public:
  using DL = DoubleLinkList<T, V>;
  using DLN = typename DoubleLinkList<T, V>::DN;
  LRUCache(size_t cap) : cap_(cap) {}

  void MakeRecently(T key) {
    auto iter = map_.find(key);
    if (iter == map_.end()) {
      return;
    }
    list_.Remove((iter->second));
    list_.PushBack((iter->second));
  }

  void AddRecently(T key, V value) {
    DLN *pNewNode = new DLN(key, value);
    list_.PushBack(pNewNode);
    map_[key] = pNewNode;
  }

  void DeleteKey(T key) {
    auto iter = map_.find(key);
    if (iter == map_.end()) {
      return;
    }
    DLN *pNode = iter->second;
    list_.Remove(pNode);
    map_.erase(iter);
    delete pNode;
  }

  void RemoveLeastRecently() {
    DLN *pNode = list_.PopFirst();
    if (pNode == nullptr) {
      return;
    }
    auto itr = map_.find(pNode->key_);
    if (itr != map_.end()) {
      map_.erase(itr);
    }
    delete pNode;
  }

  const V *Get(T t) const {
    auto iter = map_.find(t);
    if (iter == map_.end()) {
      return nullptr;
    }
    MakeRecently(t);
    return &(iter->second)->value_;
  }

  V *Get(T t) {
    auto iter = map_.find(t);
    if (iter == map_.end()) {
      return nullptr;
    }
    MakeRecently(t);
    return &(iter->second)->value_;
  }

  void Put(T t, V v) {
    if (map_.count(t)) {
      this->DeleteKey(t);
      this->AddRecently(t, v);
      return;
    }
    if (cap_ == map_.size()) {
      RemoveLeastRecently();
    }
    this->AddRecently(t, v);
  }

private:
  std::unordered_map<T, DLN *> map_;
  DL list_;
  size_t cap_;
};

#endif /* FB614393_1C69_4704_9AB7_B14334DABAA7 */
