#ifndef F828622B_1437_47D6_B9E2_B046A7E31627
#define F828622B_1437_47D6_B9E2_B046A7E31627
#include "../header.h"
#include <cstdint>

template <typename T> struct SkipNode {
  T value;
  SkipNode<T> **nextList = nullptr;
};

template <typename T, int MaxLevel = 10> class SkipList {
public:
  using SN = SkipNode<T>;
  SkipList() {
    head = new SN();
    head->nextList = new SN *[MaxLevel + 1]();
    for (int i = 0; i <= MaxLevel; i++) {
      LOG(INFO) << head->nextList[i];
      head->nextList[i] = nullptr;
    }
    level_ = 0;
  }
  // TODO
  ~SkipList(){

  };

  void insert(T value) {
    SN *cur = head;
    SN *update[MaxLevel + 1] = {};

    //从最高级，一层层往下找出前置节点，当i==0时，找出来的就是新增节点的前置节点，因为没有高度的节点他的nextlist[0]指向的是下一个节点
    //取出要更新的节点
    for (int i = level_; i >= 0; i--) {
      while (cur->nextList[i] && cur->nextList[i]->value < value) {
        cur = cur->nextList[i];
      }
      update[i] = cur;
    }

    //取出后置节点
    cur = cur->nextList[0];

    // 如果要插入的节点已存在，则直接返回,如果值一样，则不会出现相同的值两遍
    if (cur && cur->value == value) {
      return;
    }

    int newLevel = randomLevel();
    //如果新增节点大于现有的,要修改的节点要包括首节点,首节点要全部指向新增的层数
    if (newLevel > level_) {
      for (int i = level_ + 1; i <= newLevel; i++) {
        update[i] = head;
      }
      level_ = newLevel;
    }
    SN *newNode = new SN();
    newNode->value = value;
    newNode->nextList = new SN *[newLevel + 1];
    for (int i = 0; i <= newLevel; i++) {
      newNode->nextList[i] = update[i]->nextList[i];
      update[i]->nextList[i] = newNode;
    }
    size_++;
  }
  bool remove(T &value) {
    SN *update[MaxLevel] = {};
    SN *cur = head;

    //重新找出前置节点
    for (int i = level_; i >= 0; i--) {
      while (cur->nextList[i] && cur->nextList[i]->value < value) {
        cur = cur->nextList[i];
      }
      update[i] = cur;
    }
    cur = cur->nextList[0];

    //如果要删除的节点不存在，则直接返回
    if (!cur || cur->value != value) {
      return false;
    }

    //更新前置节点的下一个节点为下下个节点
    for (int i = 0; i <= level_; i++) {
      if (update[i]->nextList[i] == cur) {
        update[i]->nextList[i] = cur->nextList[i];
      }
    }
    return true;
  }

  bool contains(const T &value) {
    const SN *cur = head;
    for (int i = level_; i >= 0; i--) {
      while (cur->nextList[i] && cur->nextList[i]->value < value) {
        cur = cur->nextList[i];
      }
    }
    //
    if (cur && cur->nextList[0]) {
      LOG(INFO) << "find target before:" << cur->value;
      return cur->nextList[0]->value == value;
    }
    return false;
  }

  SN *Search(const T &t) {
    const SN *start = head;
    for (int i = level_; i >= 0; i--) {
      while (start->nextList[i] && start->nextList[i]->value < t) {
        start = start->nextList[i];
      }
    }
    if (start && start->nextList[0]) {
      if (start->nextList[0]->value == t) {
        return start->nextList[0];
      }
    }
    return nullptr;
  }

  void clear() {
    SN *start = head;
    int i = 0;
    while (start) {
      SN *temp = start;
      start = start->nextList[0];
      delete temp;
      LOG(INFO) << "do clear!" << ++i;
    }
    size_ = 0;
    level_ = 0;
    LOG(INFO) << "do clear!";
  }
  //   int size();
  void print() {
    SN *start = head;
    while (start) {
      LOG(INFO) << start->value;
      start = start->nextList[0];
    }
  }

private:
  int level_ = 0;
  int size_ = 0;
  SkipNode<T> *head = nullptr;
  SkipNode<T> *tail = nullptr;
  std::vector<SkipNode<T> *> skipList;
  std::vector<int> *skipListLevel;
  int randomLevel() {
    int level = 0;
    while (rand() % 2 == 1 && level < MaxLevel) {
      level++;
    }
    return level;
  }
  void printSkipList();
};

#endif /* F828622B_1437_47D6_B9E2_B046A7E31627 */
