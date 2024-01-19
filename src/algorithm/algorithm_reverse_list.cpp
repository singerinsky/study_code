#include "../header.h"
#include "algorithm_double_linklist.h"

TEST(LinkListTest, Insert) {
  LinkList<int, char> list;
  ListNode<int, char> *pNode = new ListNode<int, char>(10, 'a');
  ListNode<int, char> *pNode1 = new ListNode<int, char>(11, 'a');
  ListNode<int, char> *pNode2 = new ListNode<int, char>(12, 'a');
  ListNode<int, char> *pNode3 = new ListNode<int, char>(13, 'a');
  ListNode<int, char> *pNode4 = new ListNode<int, char>(14, 'a');
  ListNode<int, char> *pNode5 = new ListNode<int, char>(15, 'a');
  list.Insert(pNode);
  list.Insert(pNode1);
  list.Insert(pNode2);
  list.Insert(pNode3);
  list.Insert(pNode4);
  list.Insert(pNode5);
  EXPECT_EQ(list.GetSize(), 6);
  list.Foreach([](ListNode<int, char> *pNode) { LOG(INFO) << pNode->key_; });
}

// Test Remove function
TEST(LinkListTest, Remove) {
  LinkList<int, char> list;
  ListNode<int, char> *pNode1 = new ListNode<int, char>(10, 'a');
  ListNode<int, char> *pNode2 = new ListNode<int, char>(20, 'b');
  ListNode<int, char> *pNode3 = new ListNode<int, char>(30, 'c');
  list.Insert(pNode1);
  list.Insert(pNode2);
  list.Insert(pNode3);
  list.Remove(pNode2);
  EXPECT_EQ(list.GetSize(), 2);
}

// Test PopFirst function
TEST(LinkListTest, PopFirst) {
  LinkList<int, char> list;
  ListNode<int, char> *pNode1 = new ListNode<int, char>(10, 'a');
  ListNode<int, char> *pNode2 = new ListNode<int, char>(20, 'b');
  ListNode<int, char> *pNode3 = new ListNode<int, char>(30, 'c');
  list.Insert(pNode1);
  list.Insert(pNode2);
  list.Insert(pNode3);
  ListNode<int, char> *pRemove = list.PopFirst();
  EXPECT_EQ(list.GetSize(), 2);
  EXPECT_EQ(pRemove->key_, 30);
}

// Test Resverse function
TEST(LinkListTest, Resverse) {
  // 创建一个新的链表，其值为 1, 2, 3
  LinkList<int, char> list = LinkList<int, char>();
  ListNode<int, char> *pNode1 = new ListNode<int, char>(10, 'a');
  ListNode<int, char> *pNode2 = new ListNode<int, char>(20, 'b');
  ListNode<int, char> *pNode3 = new ListNode<int, char>(30, 'c');
  list.Insert(pNode1);
  list.Insert(pNode2);
  list.Insert(pNode3);

  // 对链表进行反转
  ResverseLinkList<int, char>(list);

  // 检查链表的元素是否为 3, 2, 1
  // EXPECT_EQ(list.GetHead()->next, nullptr);
  list.Foreach([](ListNode<int, char> *pNode) { LOG(INFO) << pNode->key_; });
  // EXPECT_EQ(list.GetHead()->next->value_, 'a');
  //  EXPECT_EQ(list.GetHead()->next->next->value_, 2);
  //  EXPECT_EQ(list.GetHead()->next->next->next->value_, 1);
}