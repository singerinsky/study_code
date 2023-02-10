#include "header.h"
#include "test_stl.h"
#include <list>
#include <functional>
#include "util/class_sample.h"

void dump_node(int& value)
{
    LOG(INFO)<<value;
}

TEST(TestAVL,avl_1)
{
    AvlTree<int> tree;
    TreeNode<int> node;
    auto newNode = new TreeNode<int>(1);
    auto newNode3 = new TreeNode<int>(3);
    auto newNode2 = new TreeNode<int>(2);
    tree.Insert(newNode);
    tree.Insert(newNode2);
    tree.Insert(newNode3);
    tree.doforeach(dump_node);
}

TEST(TestStl,vec_1)
{
    std::vector<int> vec;
    std::vector<int>::size_type count = vec.size();
}

TEST(TestQueuePop,test_1)
{
    std::queue<int,std::list<int>> queue_with_list_src;
    std::queue<int,std::list<int>> queue_with_list_rst;

}

void function_pre_build(int value1,int value2)
{
    LOG(INFO)<<"value1"<<value1<<" value2"<<value2;
}

using namespace std::placeholders;

TEST(TestStl,bind)
{
    auto func = std::bind(function_to_bind,4);
    func();
    auto func_use_hold = std::bind(function_pre_build,4,_1);
    func_use_hold(999);
}

TEST(TestStl,void_value)
{
    test_void<void>();
    test_void<int>();
}

void test_function_ref(int i )
{
    LOG(INFO)<<"in value is "<<i;
}

template<class Func>
void warp_function(int i ,Func & func){
    func(i);
}

template<class Func>
void warp_function(int j,int i ,Func  func){
    func(i+j);
}


TEST(TestStl,ref_function){
    warp_function(1,test_function_ref);
    warp_function(1,1,test_function_ref);
    ClassWithInitializer object = {{"guanlei","age"}};
    object.dump();
}

TEST(Test20,init)
{
    int age {111};

    LOG(INFO)<<"age:"<<age;
}






