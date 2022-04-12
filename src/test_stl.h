#ifndef FCA815B9_0C14_495F_A5AF_929C844BAE5A
#define FCA815B9_0C14_495F_A5AF_929C844BAE5A

template <class T>
struct TreeNode {
    TreeNode()
    {
        parentNode_ = nullptr;
        leftNode_ = nullptr;
        rightNode_ = nullptr;
    }
    TreeNode(T t)
    {
        parentNode_ = nullptr;
        leftNode_ = nullptr;
        rightNode_ = nullptr;
        value_ = t;
    }
    TreeNode* parentNode_;
    TreeNode* leftNode_;
    TreeNode* rightNode_;
    T value_;
};

template <class T>
struct AvlTree {
    typedef TreeNode<T> Node;
    Node* root_ = nullptr;
    int CalcHeight()
    {
        return _Height(root_);
    }

    void Insert(Node* newNode)
    {
        insertAvl(&root_, newNode);
    }

    void doforeach(std::function<void(T& t)> func, Node* node = nullptr)
    {
        _doforeach(func, root_);
    }

private:
    int _Height(Node* node)
    {
        int left, right;
        if (node == nullptr)
            return -1;
        left = _Height(node->leftNode_);
        right = _Height(node->rightNode_);
        return left > right ? left : right;
    }
    //左左旋转
    void RotationLeftOnce(Node** node)
    {
        Node* node0;
        node0 = (*node)->leftNode_;
        (*node)->leftNode_ = node0->rightNode_;
        node0->rightNode_ = *node;
        *node = node0;
    }

    //右右旋转
    void RotationRightOnce(Node** node)
    {
        Node* node0 = (*node)->rightNode_;
        (*node)->rightNode_ = node0->leftNode_;
        node0->leftNode_ = *node;
        *node = node0;
    }
    //左右
    void RotationLeftRight(Node** node)
    {
        RotationRightOnce(&(*node)->leftNode_);
        RotationLeftOnce(node);
    }
    //右左
    void RotationRightLeft(Node** node)
    {
        RotationLeftOnce(&(*node)->rightNode_);
        RotationRightOnce(node);
    }

    void insertAvl(Node** currentNode, Node* newNode)
    {
        if (*currentNode == nullptr) {
            *currentNode = newNode;
            return;
        }
        if (newNode->value_ > (*currentNode)->value_) {
            insertAvl(&((*currentNode)->rightNode_), newNode);
            if (1 == _Height((*currentNode)->rightNode_) - _Height((*currentNode)->leftNode_)) {
                if (newNode->value_ > (*currentNode)->rightNode_->value_)
                    RotationRightOnce(currentNode);
                else
                    RotationRightLeft(currentNode);
            }
        } else {
            insertAvl(&(*currentNode)->leftNode_, newNode);
            if (1 == _Height((*currentNode)->leftNode_) - _Height((*currentNode)->rightNode_)) {
                if (newNode->value_ < (*currentNode)->leftNode_->value_)
                    RotationLeftOnce(currentNode);
                else {
                    RotationLeftRight(currentNode);
                }
            }
        }
    }
    void _doforeach(std::function<void(T& t)> func, Node* node)
    {
        if (node == nullptr)
            return;
        _doforeach(func, node->leftNode_);
        func(node->value_);
        _doforeach(func, node->rightNode_);
    }
};

//前序
template <class T>
void preorder(TreeNode<T>* rootNode)
{
    if (rootNode == nullptr)
        return;

    LOG(INFO) << rootNode->value_;
    preorder(rootNode->leftNode_);
    preorder(rootNode->rightNode_);
}
//中序
template <class T>
void middleorder(TreeNode<T>* rootNode)
{
    if (rootNode == nullptr)
        return;

    preorder(rootNode->leftNode_);
    LOG(INFO) << rootNode->value_;
    preorder(rootNode->rightNode_);
}
//后序
template <class T>
void postorder(TreeNode<T>* rootNode)
{
    if (rootNode == nullptr)
        return;

    postorder(rootNode->leftNode_);
    postorder(rootNode->rightNode_);
    LOG(INFO) << rootNode->value_;
}

//查找
template <class T>
bool avlfind(T& value, TreeNode<T>* rootNode)
{
    if (rootNode == nullptr) {
        return false;
    }
    if (rootNode->value_ == value) {
        return true;
    } else if (rootNode->value_ < value) {
        return avlfind(value, rootNode->rightNode_);
    } else {
        return avlfind(value, rootNode->leftNode_);
    }
}

template <class T>
void insertAvl(AvlTree<T>* tree, TreeNode<T>* newNode)
{
    if (tree->root_ == nullptr)
        tree->root_ = newNode;
}

//test pop and move

void function_to_bind(int value)
{
    LOG(INFO) << "VALUE :" << value;
} 

template<class T>
std::enable_if_t<std::is_void<T>::value,T> test_void(){
    LOG(INFO)<<" void";
}


template<class T>
std::enable_if_t<!std::is_void<T>::value,T> test_void(){
    LOG(INFO)<<" not void";
    return T(0);
}


#endif /* FCA815B9_0C14_495F_A5AF_929C844BAE5A */
