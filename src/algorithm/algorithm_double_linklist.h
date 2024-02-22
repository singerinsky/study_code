#ifndef BB3A7CD2_35A4_4592_8A1E_1C297CE30D1A
#define BB3A7CD2_35A4_4592_8A1E_1C297CE30D1A

#include <functional>
#include <glog/logging.h>
#include <sys/types.h>
#include <unistd.h>

template <typename K, typename T> class ListNode {
public:
  ListNode<K, T> *next;
  T value_;
  K key_;

  ListNode() : next(nullptr) {
    key_ = K();
    value_ = T();
  }

  ListNode(K k, T t) : next(nullptr) {
    key_ = k;
    value_ = t;
  }
};

template <typename K, typename T> class LinkList {
public:
  using LN = ListNode<K, T>;
  LinkList() {
    head_ = new LN(999, 999);
    tail_ = new LN(888, 888);
    head_->next = tail_;
    size_ = 0;
  }

  ~LinkList() {
    LN *pTemp = head_;
    while (pTemp->next != tail_) {
      LN *pNext = pTemp->next;
      delete pTemp;
      pTemp = pNext;
    }
    delete pTemp;
    delete tail_;
  }

  void Insert(LN *pNode) {
    pNode->next = head_->next;
    head_->next = pNode;
    size_++;
  }

  void Remove(LN *pNode) {
    LN *pTemp = head_;
    while (pTemp->next != tail_) {
      if (pTemp->next == pNode) {
        pTemp->next = pNode->next;
        size_--;
        return;
      }
      pTemp = pTemp->next;
    }
  }

  LN *PopFirst() {
    if (head_->next == tail_) {
      return nullptr;
    }
    LN *pRemove = head_->next;
    head_->next = pRemove->next;
    size_--;
    return pRemove;
  }

  size_t GetSize() { return size_; }

  const LN *GetHead() const { return head_; }

  LN *GetHead() { return head_; }

  const LN *GetTail() const { return tail_; }

  LN *GetTail() { return tail_; }

  void Foreach(std::function<void(LN *)> func) {
    auto *pTemp = head_;
    while (pTemp->next != tail_) {
      func(pTemp->next);
      pTemp = pTemp->next;
      sleep(1);
    }
  }

private:
  LN *head_;
  LN *tail_;
  size_t size_;
};
/*
函数的实现使用了一个 lambda 函数
_resverse，该函数接受一个链表和一个节点作为参数。如果当前节点的下一个节点就是链表的尾节点，那么就返回当前节点。否则，它会递归调用
_resverse
函数，将当前节点的下一个节点作为参数，并将返回的节点的下一个节点设置为当前节点，然后将当前节点的下一个节点设置为链表的尾节点。最后，它返回最后一次递归调用
_resverse 函数的结果。

在函数的最后，它创建了一个指向链表头节点的指针pLastNode，并将其设置为 _resverse
函数的返回值，即反转后的链表的尾节点。然后，它将链表的头节点的下一个节点设置为pLastNode，完成了链表的反转。*/
template <typename K, typename T> void ResverseLinkList(LinkList<K, T> &list) {
  std::function<typename LinkList<K, T>::LN *(LinkList<K, T> &,
                                              typename LinkList<K, T>::LN *)>
      _resverse =
          [&](LinkList<K, T> &list, typename LinkList<K, T>::LN *node_start) ->
      typename LinkList<K, T>::LN * {
        if (node_start->next == list.GetTail()) {
          return node_start;
        }
        typename LinkList<K, T>::LN *last = _resverse(list, node_start->next);
        node_start->next->next = node_start;

        node_start->next = list.GetTail();

        return last;
      };
  //返回的是新的头指针
  auto *pLastNode = _resverse(list, list.GetHead()->next);
  //设置head指向新的指针
  list.GetHead()->next = pLastNode;
}

// 反转链表
template <typename K, typename T>
ListNode<K, T> *_GetResverseList(ListNode<K, T> *cur, ListNode<K, T> *cur_pre) {
  if (cur == nullptr) {
    return cur_pre;
  }
  ListNode<K, T> *head_after_resvese = _GetResverseList(cur->next, cur);
  cur->next = cur_pre;
  return head_after_resvese;
}

// 分区链表
template <typename K, typename T>
ListNode<K, T> *GetPartitionList(ListNode<K, T> *header, T t) {
  if (header == nullptr) {
    return header;
  }
  ListNode<K, T> *pLarge = new ListNode<K, T>();
  auto pLargeHeader = pLarge;
  ListNode<K, T> *pSmall = new ListNode<K, T>();
  auto pSmallHeader = pSmall;
  while (header->next != nullptr) {
    if (header->value_ < t) {
      pSmall->next = header;
      pSmall = pSmall->next;
    } else {
      pLarge->next = header;
      pLarge = pLarge->next;
    }
    header = header->next;
  }
  pLarge->next = nullptr;
  pSmall->next = pLargeHeader;
  return pSmallHeader;
}
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
