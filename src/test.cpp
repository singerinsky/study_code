/*
 * @file:
 * @copyright: 2012 - 2028 ByteDance. All Rights Reserved
 * @Author: guanlei
 * @Date: 2021-10-25 19:33:49
 * @brief:
 */
#include <iostream>
#include "gtest/gtest.h"
#include "test_case/c_11.h"
#include <map>
#include <memory>
#include <thread>   // std::thread
#include <string>   // std::string
#include <future>   // std::promise, std::future
#include <chrono>   // seconds
#include "test_case/test_thread.h"
#include "test_case/test_stack.h"
#include "wsstackrecorder.h"

using namespace std;
void function_util();
int other_call()
{
    printf("Hello World!");

    std::string r = "1111";
    std::string l = std::move(r);
    printf("i = %s", l.c_str());

    function_util();
    printf("\n");
    return 0;
}



class A
{

public:
    A() = default;
    A(int value)
    {
        i = value;
        printf("Consc A...\n");
    }

    ~A()
    {
        printf("Desc A...\n");
    }
    int i = 11;
};

void test_auto()
{
    int** i = new int* [10];
    int* p = new int;
    int* array[10];
    int  valueArray[10];
    for (int index = 0; index < 10; index++)
    {
        array[index] = new int;
        *array[index] = index;
        valueArray[index] = index;
    }

    for (auto ptr : array)
    {
        printf("%s\n", typeid(ptr).name());
    }
    for (const auto& index : valueArray)
    {
        printf("%s\n", typeid(index).name());
        const_cast<int&>(index)  = 0;
    }

    auto unique_ptr = std::make_unique<int>();
    *unique_ptr = 10;
    std::cout << *unique_ptr;

    auto aPtr = std::make_unique<A>();
    aPtr->i = 1111;
    A a = {123123};
    std::vector<A> vecA = {{11}, {22}};
    printf("%ld size", vecA.size());
}


void test_emplace()
{
    std::map<int, std::unique_ptr<int>> test_map;
    auto p = std::make_unique<int>();
    //auto p1(new int);
    //printf("%s",typeid(p1).name());
    *p = 111;
    //test_map.emplace(1,p);

    std::map<int, std::shared_ptr<A>> shared_map;
    auto share_ptr = std::make_shared<A>();
    share_ptr->i = 900;
    shared_map.emplace(1, share_ptr);

    for (auto&& kev : shared_map )
    {
        std::cout << kev.first << endl;
    }

}



using function_ptr = void(*)();

using namespace std::chrono;

void read(std::future<std::string>* future)
{
    // future会一直阻塞，直到有值到来
    std::cout << future->get() << std::endl;
}

int test_promise()
{
    auto task = [](std::future<int> fValue)
    {
        printf("start task");
        printf("%d\n", fValue.get());
    };

    std::promise<int> pValue;
    auto rst = std::async(std::launch::async, task, pValue.get_future());
    //std::thread t{ task, pValue.get_future() };
    std::this_thread::sleep_for(std::chrono::seconds(5));
    pValue.set_value(5);
    //t.join();

    return 0;
}

int sleep_function()
{

    std::this_thread::sleep_for(std::chrono::seconds(5));
    return (int)time(nullptr);
}

void test_aysnc()
{
    //std::future<int> the_answer = std::async(sleep_function);
    auto the_answer = std::async(sleep_function);
    printf("--------------------\n");
    printf("%ld\n", time(nullptr));
    printf("------------return value %d------", the_answer.get());
}

void test_des_aysnc()
{
    auto sleep = [](int s)
    {
        std::this_thread::sleep_for(std::chrono::seconds(s));
    };
    {
        auto f = std::async( std::launch::async, sleep, 5 ); // 开启一个异步任务，睡眠 5s
        // future 对象析构，等待睡眠结束
    }
}

int f(int)
{
    printf("sss\n");
    return 0;
}

class SClass
{
public:
    SClass(int param): _param(param) {}
    ~SClass() {}
private:
    int _param;
};

class ClassFunction
{
public:
    ~ClassFunction()
    {
        printf("disconut!");
    }

public:
    std::function<int(int)> m_function;
};

std::unique_ptr<ClassFunction> function_get_unique_ptr()
{
    auto ptr = std::make_unique<ClassFunction>();
    return ptr;
}

void function_move(std::string& str)
{
    std::string st = std::move(str);
    std::cout << st << endl;
}


void test_map()
{
    std::map<int, int> map1_;
    map1_[1] = 11;
    map1_[2] = 11;
    map1_[3] = 11;
    const auto& kv = map1_.find(1);
    std::cout << typeid(kv).name() << endl;

    for (auto& kvi : map1_)
    {
        std::cout << typeid(kvi).name() << endl;
    }

}


