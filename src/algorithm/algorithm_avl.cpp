#include "algorithm_avl.h"
#include <gtest/gtest.h>

TEST(AvlTreeTest, TestHeight) {
  AVLTree<int> tree;
  // Test the height of an empty tree
  EXPECT_EQ(tree.CalcHeight(), -1);
  // Test the height of a tree with one node
  TreeNode<int> *node = new TreeNode<int>(1);
  tree.root_ = node;
  EXPECT_EQ(tree.CalcHeight(), 0);
  // Test the height of a tree with two nodes
  TreeNode<int> *node2 = new TreeNode<int>(2);
  node->rightNode_ = node2;
  EXPECT_EQ(tree.CalcHeight(), 1);
  // Test the height of a tree with three nodes
  TreeNode<int> *node3 = new TreeNode<int>(3);
  node->leftNode_ = node3;
  EXPECT_EQ(tree.CalcHeight(), 1);
}

// Test the preorder() method of the TreeNode class
TEST(TreeNodeTest, TestPreorder) {
  TreeNode<int> *node = new TreeNode<int>(1);
  preorder(node);
  EXPECT_EQ(node->value_, 1);
  delete node;
}

// Test the middleorder() method of the TreeNode class
TEST(TreeNodeTest, TestMiddleorder) {
  TreeNode<int> *node = new TreeNode<int>(1);
  middleorder(node);
  EXPECT_EQ(node->value_, 1);
  delete node;
}

// Test the postorder() method of the TreeNode class
TEST(TreeNodeTest, TestPostorder) {
  TreeNode<int> *node = new TreeNode<int>(1);
  postorder(node);
  EXPECT_EQ(node->value_, 1);
  delete node;
}

// Test the avlfind() method of the AvlTree class
TEST(AvlTreeTest, TestAvlfind) {
  AVLTree<int> tree;
  // Test the case where the value is not found
  EXPECT_FALSE(avlfind(5, tree.root_));
  // Test the case where the value is found
  TreeNode<int> *node = new TreeNode<int>(3);
  tree.root_ = node;
  EXPECT_TRUE(avlfind(3, tree.root_));
  delete node;
}

// Test the insertAvl() method of the AvlTree class
TEST(AvlTreeTest, TestInsertAvl) {
  AVLTree<int> tree;
  // Test the case where the tree is empty
  tree.insert(new TreeNode<int>(3));
  EXPECT_EQ(tree.root_->value_, 3);
  // Test the case where the tree is not empty
  tree.insert(new TreeNode<int>(2));
  EXPECT_EQ(tree.root_->value_, 3);
  EXPECT_TRUE(tree.root_->leftNode_ != nullptr);
  EXPECT_EQ(tree.root_->leftNode_->value_, 2);
  delete tree.root_->leftNode_;
  delete tree.root_;
}
