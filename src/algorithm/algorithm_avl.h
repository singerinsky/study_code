#ifndef AVL_TREE_H
#define AVL_TREE_H
/*
这段代码实现了一个AVL树的数据结构，包括树节点的定义和AVL树的操作方法。AVL树是一种平衡二叉搜索树，可以在O(logn)的时间复杂度内进行插入、删除和查找操作。

该代码的核心是AVLTree类和TreeNode结构体。AVLTree类包含了AVL树的插入方法、计算树高度的方法和私有的平衡方法。TreeNode结构体表示树节点，包含了父节点、左子节点、右子节点和值。

AVLTree的插入方法使用递归实现，先找到节点的插入位置，然后进行平衡操作。平衡操作根据节点的左右子树高度差进行判断，如果高度差大于1或小于-1，则进行相应的旋转操作。

除了插入方法，该代码还实现了查找方法avlfind()和遍历方法preorder()、middleorder()、postorder()。其中，avlfind()使用递归在树中查找指定值；preorder()、middleorder()、postorder()分别表示前序遍历、中序遍历和后序遍历。

此外，代码还提供了一个executeEachMid()函数，用于对树的每个节点执行传入的函数。该函数使用中序遍历的方式遍历树，并通过函数指针调用传入的函数。
总之，这段代码实现了一个AVL树的数据结构，并提供了插入、查找和遍历等方法，可以方便地进行AVL树的操作。
/////////////////////////////////////////////////
在AVL树中，旋转操作用于保持树的平衡。当插入或删除节点后，可能会导致树失去平衡，即某个节点的左子树和右子树高度差大于1。为了恢复平衡，需要进行旋转操作。

旋转操作分为左旋和右旋两种。左旋将一个节点的右子树提升为根节点，右子树的左子树成为该节点的右子树。右旋则是左旋的反向操作。

在代码中，左旋操作定义为_rotateLeft()，右旋操作定义为_rotateRight()。下面详细说明它们的实现过程：

左旋操作（_rotateLeft()）：

首先，创建一个临时指针temp指向当前节点的右子节点。
将当前节点的右子节点指向temp的左子节点。
如果temp的左子节点不为空，将temp的左子节点的父节点指针指向当前节点。
将temp的父节点指针指向当前节点的父节点。
如果当前节点的父节点为空，表示当前节点为根节点，则将根节点指针指向temp。
如果当前节点是其父节点的左子节点，则将当前节点的父节点的左子节点指针指向temp。
否则，将当前节点的父节点的右子节点指针指向temp。
将temp的左子节点指针指向当前节点。
将当前节点的父节点指针指向temp。
右旋操作（_rotateRight()）：

首先，创建一个临时指针temp指向当前节点的左子节点。
将当前节点的左子节点指向temp的右子节点。
如果temp的右子节点不为空，将temp的右子节点的父节点指针指向当前节点。
将temp的父节点指针指向当前节点的父节点。
如果当前节点的父节点为空，表示当前节点为根节点，则将根节点指针指向temp。
如果当前节点是其父节点的右子节点，则将当前节点的父节点的右子节点指针指向temp。
否则，将当前节点的父节点的左子节点指针指向temp。
将temp的右子节点指针指向当前节点。
将当前节点的父节点指针指向temp。
这两个旋转操作都会改变树的结构，以保持平衡。旋转操作的触发是在插入节点后进行平衡检查，并根据节点的左右子树高度差来判断需要进行的旋转操作。

在平衡方法balance()中，首先通过_height()方法计算节点的左右子树高度差。如果高度差大于1，则执行左旋或右旋操作，以恢复平衡。具体的旋转操作根据节点的左右子树的高度差来决定，以保证左子树高度大于等于右子树高度。
*/

#include <functional>
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

template <class T>
void executeEachMid(TreeNode<T> *rootNode, std::function<void(T *)> &func) {

  if (rootNode == nullptr)
    return;

  executeEachMid(rootNode->leftNode_, func);
  func(&(rootNode->value_));
  executeEachMid(rootNode->rightNode_, func);
}

#endif /* AVL_TREE_H */
