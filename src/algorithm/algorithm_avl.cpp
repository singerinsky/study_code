#include "algorithm_avl.h"
#include <gtest/gtest.h>
/*
这段代码是一个 C++的单元测试程序，用于测试 AVL
树的一些基本操作，包括插入、查找和删除等。以下是对这段代码的逐行解释：

#include "algorithm_avl.h"：这是一个包含 AVL 树实现的头文件。

#include <gtest/gtest.h>：这是一个包含 Google Test 框架的头文件。

TEST(AvlTreeTest, TestHeight) {...}：这是一个测试用例，用于测试 AVL
树的高度计算函数。这个测试用例中，创建了一个空树，然后测试只有一个节点的树的高度，以及有两个节点的树的高度，最后测试有三个节点的树的高度。

TEST(TreeNodeTest, TestPreorder) {...}：这是一个测试用例，用于测试 TreeNode 类的
preorder()方法。这个测试用例中，创建了一个 TreeNode 对象，然后调用
preorder()方法并检查返回值。

TEST(TreeNodeTest, TestMiddleorder) {...}：这是一个测试用例，用于测试 TreeNode
类的 middleorder()方法。这个测试用例中，创建了一个 TreeNode 对象，然后调用
middleorder()方法并检查返回值。

TEST(TreeNodeTest, TestPostorder) {...}：这是一个测试用例，用于测试 TreeNode
类的 postorder()方法。这个测试用例中，创建了一个 TreeNode 对象，然后调用
postorder()方法并检查返回值。

TEST(AvlTreeTest, TestAvlfind) {...}：这是一个测试用例，用于测试 AVL 树的
avlfind()方法。这个测试用例中，创建了一个 AVL
树，然后测试值未找到的情况，以及值找到的情况。

TEST(AvlTreeTest, TestInsertAvl) {...}：这是一个测试用例，用于测试 AVL 树的
insertAvl()方法。这个测试用例中，创建了一个 AVL
树，然后测试树为空的情况，以及树不为空的情况。

class AVLTreeTest : public testing::Test {...}：这是一个测试类，继承自 Google
Test 的 Test 类。在这个类中，定义了一个 AVL 树，并提供了一些测试方法。

void SetUp() override {...}：这是 Test
类的一个虚函数，在每个测试用例运行前会被调用。在这个函数中，创建了一个 AVL 树。

void TearDown() override {...}：这是 Test
类的一个虚函数，在每个测试用例运行后会被调用。在这个函数中，删除了创建的 AVL
树。

TEST(AVLTreeTest, FunctionTest)
{...}：这是一个测试用例，用于测试给定的函数是否按预期工作。这个测试用例中，创建了一个
AVL 树，然后调用给定的函数，并检查返回值。

*/
TEST(AvlTreeTest, TestHeight) {
  AVLTree<int> tree;
  // 测试空树的高度
  EXPECT_EQ(tree.CalcHeight(), -1);
  // 测试只有一个节点的树的高度
  TreeNode<int> *node = new TreeNode<int>(1);
  tree.root_ = node;
  EXPECT_EQ(tree.CalcHeight(), 0);
  // 测试有两个节点的树的高度
  TreeNode<int> *node2 = new TreeNode<int>(2);
  node->rightNode_ = node2;
  EXPECT_EQ(tree.CalcHeight(), 1);
  // 测试有三个节点的树的高度
  TreeNode<int> *node3 = new TreeNode<int>(3);
  node->leftNode_ = node3;
  EXPECT_EQ(tree.CalcHeight(), 1);
}

// 测试 TreeNode 类的 preorder() 方法
TEST(TreeNodeTest, TestPreorder) {
  TreeNode<int> *node = new TreeNode<int>(1);
  preorder(node);
  EXPECT_EQ(node->value_, 1);
  delete node;
}

// 测试 TreeNode 类的 middleorder() 方法
TEST(TreeNodeTest, TestMiddleorder) {
  TreeNode<int> *node = new TreeNode<int>(1);
  middleorder(node);
  EXPECT_EQ(node->value_, 1);
  delete node;
}

// 测试 TreeNode 类的 postorder() 方法
TEST(TreeNodeTest, TestPostorder) {
  TreeNode<int> *node = new TreeNode<int>(1);
  postorder(node);
  EXPECT_EQ(node->value_, 1);
  delete node;
}

// 测试 AvlTree 类的 avlfind() 方法
TEST(AvlTreeTest, TestAvlfind) {
  AVLTree<int> tree;
  // 测试值未找到的情况
  EXPECT_FALSE(avlfind(5, tree.root_));
  // 测试值找到的情况
  TreeNode<int> *node = new TreeNode<int>(3);
  tree.root_ = node;
  EXPECT_TRUE(avlfind(3, tree.root_));
  delete node;
}

// 测试 AvlTree 类的 insertAvl() 方法
TEST(AvlTreeTest, TestInsertAvl) {
  AVLTree<int> tree;
  // 测试树为空的情况
  tree.insert(new TreeNode<int>(3));
  EXPECT_EQ(tree.root_->value_, 3);
  // 测试树不为空的情况
  tree.insert(new TreeNode<int>(2));
  EXPECT_EQ(tree.root_->value_, 3);
  EXPECT_TRUE(tree.root_->leftNode_ != nullptr);
  EXPECT_EQ(tree.root_->leftNode_->value_, 2);
  delete tree.root_->leftNode_;
  delete tree.root_;
}

class AVLTreeTest : public testing::Test {
protected:
  void SetUp() override {
    tree_ = new AVLTree<int>();
    auto *node = new TreeNode<int>(1);
    tree_->root_ = node;
    node->leftNode_ = new TreeNode<int>(2);
    node->rightNode_ = new TreeNode<int>(3);
    node->leftNode_->leftNode_ = new TreeNode<int>(4);
    node->leftNode_->rightNode_ = new TreeNode<int>(5);
  }

  void TearDown() override { delete tree_; }

  AVLTree<int> *tree_;
};

/**
 * @brief 测试函数
 * @details 用于测试给定的函数是否按预期工作
 * @param TreeNode<T> *rootNode 要测试的树节点
 * @param std::function<void(T *)> &func 要执行的函数
 */
TEST(AVLTreeTest, FunctionTest) {
  TreeNode<int> *rootNode = new TreeNode<int>(1);
  rootNode->leftNode_ = new TreeNode<int>(2);
  rootNode->rightNode_ = new TreeNode<int>(3);
  rootNode->leftNode_->leftNode_ = new TreeNode<int>(4);
  rootNode->leftNode_->rightNode_ = new TreeNode<int>(5);

  std::function<void(int *)> func = [](int *num) {
    LOG(INFO) << "int for each:" << *num << std::endl;
  };

  executeEachMid(rootNode, func);

  delete rootNode;
}