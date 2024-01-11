#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <glog/logging.h>

template <class T> struct TreeNode {
  TreeNode *parentNode_;
  TreeNode *leftNode_;
  TreeNode *rightNode_;
  T value_;

  TreeNode(T value) : value_(value) {}
};

template <class T> class AVLTree {
public:
  AVLTree() {}
  TreeNode<T> *root_ = nullptr;

  void insert(TreeNode<T> *newNode) {
    if (root_ == nullptr)
      root_ = newNode;
    else
      insert(root_, newNode);
  }

  int CalcHeight() {
    int height = 0;
    height = _height(root_);
    return height;
  }

  int _height(TreeNode<T> *node) {
    int left, right;
    if (node == nullptr)
      return -1;
    left = _height(node->leftNode_) + 1;
    right = _height(node->rightNode_) + 1;
    return left > right ? left : right;
  }

private:
  void insert(TreeNode<T> *node, TreeNode<T> *newNode) {
    if (newNode->value_ < node->value_) {
      if (node->leftNode_ == nullptr)
        node->leftNode_ = newNode;
      else
        insert(node->leftNode_, newNode);
    } else {
      if (node->rightNode_ == nullptr)
        node->rightNode_ = newNode;
      else
        insert(node->rightNode_, newNode);
    }
    balance(node);
  }

  void _rotateLeft(TreeNode<T> *&node) {
    TreeNode<T> *temp = node->rightNode_;
    node->rightNode_ = temp->leftNode_;
    if (temp->leftNode_ != nullptr)
      temp->leftNode_->parentNode_ = node;
    temp->parentNode_ = node->parentNode_;
    if (node->parentNode_ == nullptr)
      root_ = temp;
    else if (node == node->parentNode_->leftNode_)
      node->parentNode_->leftNode_ = temp;
    else
      node->parentNode_->rightNode_ = temp;
    temp->leftNode_ = node;
    node->parentNode_ = temp;
  }

  void _rotateRight(TreeNode<T> *&node) {
    TreeNode<T> *temp = node->leftNode_;
    node->leftNode_ = temp->rightNode_;
    if (temp->rightNode_ != nullptr)
      temp->rightNode_->parentNode_ = node;
    temp->parentNode_ = node->parentNode_;
    if (node->parentNode_ == nullptr)
      root_ = temp;
    else if (node == node->parentNode_->rightNode_)
      node->parentNode_->rightNode_ = temp;
    else
      node->parentNode_->leftNode_ = temp;
    temp->rightNode_ = node;
    node->parentNode_ = temp;
  }

  void balance(TreeNode<T> *&node) {
    int balance = _height(node->leftNode_) - _height(node->rightNode_);
    if (balance > 1) {
      if (_height(node->leftNode_->leftNode_) >=
          _height(node->leftNode_->rightNode_))
        _rotateRight(node);
      else
        _rotateLeft(node->leftNode_), _rotateRight(node);
    } else if (balance < -1) {
      if (_height(node->rightNode_->rightNode_) >=
          _height(node->rightNode_->leftNode_))
        _rotateLeft(node);
      else
        _rotateRight(node->rightNode_), _rotateLeft(node);
    }
  }
};

//查找
template <class T> bool avlfind(const T &value, TreeNode<T> *node) {
  if (node == nullptr) {
    return false;
  }
  if (node->value_ == value) {
    return true;
  } else if (node->value_ < value) {
    return avlfind(value, node->rightNode_);
  } else {
    return avlfind(value, node->leftNode_);
  }
}

template <class T> void preorder(TreeNode<T> *rootNode) {
  if (rootNode == nullptr)
    return;

  LOG(INFO) << rootNode->value_;
  preorder(rootNode->leftNode_);
  preorder(rootNode->rightNode_);
}

template <class T> void middleorder(TreeNode<T> *rootNode) {
  if (rootNode == nullptr)
    return;

  preorder(rootNode->leftNode_);
  LOG(INFO) << rootNode->value_;
  preorder(rootNode->rightNode_);
}

template <class T> void postorder(TreeNode<T> *rootNode) {
  if (rootNode == nullptr)
    return;

  postorder(rootNode->leftNode_);
  postorder(rootNode->rightNode_);
  LOG(INFO) << rootNode->value_;
}

#endif /* AVL_TREE_H */
