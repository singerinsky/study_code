#ifndef BB3A7CD2_35A4_4592_8A1E_1C297CE30D1A
#define BB3A7CD2_35A4_4592_8A1E_1C297CE30D1A

#include <unistd.h>

template <typename K, typename T> class DoubleListNode {
public:
  DoubleListNode<K, T> *next;
  DoubleListNode<K, T> *prev;
  T value_;
  K key_;

  DoubleListNode() : next(nullptr), prev(nullptr) {
    key_ = K();
    value_ = T();
  }

  DoubleListNode(K k, T t) : next(nullptr), prev(nullptr) {
    key_ = k;
    value_ = t;
  }
};

template <typename K, typename T> class DoubleLinkList {
public:
  using DN = DoubleListNode<K, T>;
  DoubleLinkList() {
    head_ = new DN();
    tail_ = new DN();
    head_->next = tail_;
    tail_->prev = head_;
    size_ = 0;
  }

  void PushBack(DN *pNode) {
    tail_->prev->next = pNode;
    pNode->prev = tail_->prev;
    tail_->prev = pNode;
    pNode->next = tail_;
    size_++;
  }

  void Remove(DN *pNode) {
    pNode->prev->next = pNode->next;
    pNode->next->prev = pNode->prev;
    size_--;
  }

  DN *PopFirst() {
    if (head_->next == tail_) {
      return nullptr;
    }
    DN *pRemove = head_->next;
    Remove(head_->next);
    return pRemove;
  }

  size_t GetSize() { return size_; }

  const DN *GetHead() const { return head_; }

  const DN *GetTail() const { return tail_; }

private:
  DoubleListNode<K, T> *head_;
  DoubleListNode<K, T> *tail_;
  size_t size_;
};

#endif /* BB3A7CD2_35A4_4592_8A1E_1C297CE30D1A */
