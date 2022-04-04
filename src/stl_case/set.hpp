#ifndef A31FC442_2327_44FC_9099_054C338D843A
#define A31FC442_2327_44FC_9099_054C338D843A


#include <iostream>
#include "test_template_stl.h"

template<typename T>
struct tree_node {
    typedef T value_type;
    typedef T& reference_type;
    typedef const T& const_reference_type;
    T value_;
    tree_node* parent_ = nullptr;
    tree_node* left_ = nullptr;
    tree_node* right_ = nullptr;
    tree_node(T const&value,tree_node* parent,tree_node* left,tree_node* right):value_(value),parent_(parent),left_(left),right_(right){}

    ~tree_node(){
        if(left_)delete left_;
        if(right_)delete right_;
    }
};

template<class T>
class MySet{
    typedef tree_node<T> node_type;
    node_type* root_;
    public:
    typedef T value_type;
    typedef tree_iterator<node_type> const_iterator;
    MySet():root_(nullptr){}

    ~MySet(){
        if(root_)
            delete root_;
    }

    int max_depth(node_type* root)
    {
        if(root)
            return std::max(max_depth(root->left_)+1, max_depth(root->right_)+1);
        return 0;
    }

    int depth()
    {
        return max_depth(root_);
    }

    bool insert(const T& t)
    {
        node_type** n = &root_;
        node_type* p = nullptr;
        while(*n)
        {
            if(t == (*n)->value_)
                return false;
            else {
                p = *n;
                n = t < (*n)->value_? &((*n)->left_):&((*n)->right_);
            }
        }
        *n = new node_type(t,p,nullptr,nullptr);
        return true;
    }

    bool has(const T& t)
    {
        node_type* n = root_;
        while(n)
        {
            if(t == n->value_)
                return true;
            n = t < n->value_?n->left_:n->right_;
        }
        return false;
    }

    bool is_empty()const{return root_ == nullptr;}
    const_iterator begin() const
    {
        node_type *n = root_;
        while (n->left_)
            n = n->left_;
        return const_iterator(n);
    }
    const_iterator end()const{
        return const_iterator(nullptr);
    }
};

TEST(Test_stl_copy,test_set)
{
    MySet<int> set;
    set.insert(1);
    set.insert(12);
    set.insert(13);
    set.insert(14);
    set.insert(8);
    set.insert(5);
    for(auto itr = set.begin();itr!= set.end();++itr)
    {
        LOG(INFO)<<"set:"<<*itr;
    }
    LOG(INFO)<<set.depth();
}

#endif /* A31FC442_2327_44FC_9099_054C338D843A */
