#include "header.h"


template<class T>
struct TreeNode
{
    TreeNode* parentNode_;
    TreeNode* leftNode_;
    TreeNode* rightNode_;
    T         value_;
};

template<class T>
struct AvlTree
{
    TreeNode<T>* root_ = nullptr;
    int CalcHeight()
    {
        return _Height(root_);
    }
  private:
    int _Height(TreeNode<T>* node)
    {
        int left,right;
        if(node == nullptr)
            return 0;
        left = _Height(node->leftNode_);    
        right= _Height(node->rightNode_);    
        return left > right?left:right;
    }
};

template<> 
struct TreeNode<int>;

using TreeIntNode = TreeNode<int>;

//前序
template<class T>
void preorder(TreeNode<T>* rootNode)
{
    if(rootNode == nullptr)
        return;

    LOG(INFO)<<rootNode->value_;
    preorder(rootNode->leftNode_);
    preorder(rootNode->rightNode_);
}
//中序
template<class T>
void middleorder(TreeNode<T>* rootNode)
{
    if(rootNode == nullptr)
        return;

    preorder(rootNode->leftNode_);
    LOG(INFO)<<rootNode->value_;
    preorder(rootNode->rightNode_);
}
//后序
template<class T>
void postorder(TreeNode<T>* rootNode)
{
    if(rootNode == nullptr)
        return;

    postorder(rootNode->leftNode_);
    postorder(rootNode->rightNode_);
    LOG(INFO)<<rootNode->value_;
}

//查找
template<class T>
bool avlfind(T& value,TreeNode<T>* rootNode)
{
    if(rootNode == nullptr)
    {
        return false;
    }
    if(rootNode->value_ == value)
    {
        return true;
    }else if(rootNode->value_ < value)
    {
        return avlfind(value,rootNode->rightNode_);
    }else {
        return avlfind(value,rootNode->leftNode_);
    }
}

template<class T>
void insertAvl(AvlTree<T>* tree,TreeNode<T>* newNode)
{
    if(tree->root_ == nullptr)
        tree->root_ = newNode;

}

TEST(TestAVL,avl_1)
{
    TreeNode<float>* floatNode;
    preorder(floatNode);
}

TEST(TestStl,vec_1)
{
    std::vector<int> vec;
    std::vector<int>::size_type count = vec.size();
}