#include "algorithm_double_linklist.h"
#include "../header.h"
#include <gtest/gtest.h>

// Test the PushBack function
TEST(DoubleLinkListTest, PushBack) {
  DoubleLinkList<int, std::string> list;
  DoubleListNode<int, std::string> *node1 =
      new DoubleListNode<int, std::string>(1, "Node1");
  DoubleListNode<int, std::string> *node2 =
      new DoubleListNode<int, std::string>(2, "Node2");
  list.PushBack(node1);
  list.PushBack(node2);
  EXPECT_EQ(list.GetSize(), 2);
  EXPECT_EQ(node1->next, node2);
  EXPECT_EQ(node2->prev, node1);
  EXPECT_EQ(node2->next, list.GetTail());
  EXPECT_EQ(list.GetTail()->prev, node2);
}

// Test the Remove function
TEST(DoubleLinkListTest, Remove) {
  DoubleLinkList<int, std::string> list;
  DoubleListNode<int, std::string> *node1 =
      new DoubleListNode<int, std::string>(1, "Node1");
  DoubleListNode<int, std::string> *node2 =
      new DoubleListNode<int, std::string>(2, "Node2");
  list.PushBack(node1);
  list.PushBack(node2);
  list.Remove(node1);
  EXPECT_EQ(list.GetSize(), 1);
  EXPECT_EQ(node2->prev, list.GetHead());
  EXPECT_EQ(node2->next, list.GetTail());
}

// Test the PopFirst function
TEST(DoubleLinkListTest, PopFirst) {
  DoubleLinkList<int, std::string> list;
  DoubleListNode<int, std::string> *node1 =
      new DoubleListNode<int, std::string>(1, "Node1");
  DoubleListNode<int, std::string> *node2 =
      new DoubleListNode<int, std::string>(2, "Node2");
  list.PushBack(node1);
  list.PushBack(node2);
  DoubleListNode<int, std::string> *poppedNode = list.PopFirst();
  EXPECT_EQ(list.GetSize(), 1);
  EXPECT_EQ(poppedNode, node1);
  EXPECT_EQ(node1->prev, nullptr);
  EXPECT_EQ(node1->next, node2);
  EXPECT_EQ(node2->prev, node1);
  EXPECT_EQ(node2->next, list.GetTail());
}