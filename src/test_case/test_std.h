#ifndef __TEST_STD_H__
#define __TEST_STD_H__

#include "../header.h"
#include "test_template.h"
#include <initializer_list>
#include <mutex>
#include "../util/class_sample.h"
#include <optional>

long long ustime(void)
{
    struct timeval tv;
    long long ust;

    gettimeofday(&tv, NULL);
    ust = ((long long)tv.tv_sec) * 1000000;
    ust += tv.tv_usec;
    return ust;
}

template<class T>
void param_call(T&& t)
{
    LOG(INFO) << "common " << t;
}

void param_call(const char* str)
{
    LOG(INFO) << "call param const char*!";
}


void param_call(std::string str)
{
    LOG(INFO) << "call param string!";
}

void param_call(SampleClass&& obejct)
{
    LOG(INFO) << "call param &&!";
}

template<typename T, typename ...ArgPacks>
void function_params(T&& t, ArgPacks&& ... args)
{
    LOG(INFO) << t;
    (void)std::initializer_list<int> {(param_call(std::forward<ArgPacks>(args)), 0) ...};
}


std::string get_const_string()
{
    std::string temp = "name";
    return temp;
}

std::optional<std::string> get_ref_optional(bool param = true)
{
    std::string name = "guanlei";
    if (param)
        return {name};
    else
    {
        return nullopt;
    }
}

std::string get_ref_string()
{
    std::string temp = "name";
    return temp;
}
SampleClass get_sample_class_with_rvo()
{
    SampleClass object(1);
    return object;
}

//多个分支返回不同的局部对象，就无法优化
SampleClass get_sample_class_without_nrvo()
{
    SampleClass object;
    if (time(nullptr) / 2 == 0)
    {
        object.SetId(1);
    }
    else
    {
        SampleClass object1;
        return object1;
    }
    return object;
}

//可以优化
SampleClass get_sample_class_with_nrvo()
{
    SampleClass object;
    if (time(nullptr) / 2 == 0)
    {
        object.SetId(1);
    }
    else
    {
        return object;
    }
    return object;
}

inline void scope_class_function()
{
    struct __struct_tmp_
    {
        ~__struct_tmp_()
        {
            LOG(INFO) << "release scope class!";
        }
    } scope_object;
}

template<class T>
void test_right(T&& i)
{
    LOG(INFO) << i;
    i = i * 2;
}

template<class T>
void test_right_1(T&& i)
{
    test_right(std::forward<T>(i));
}


#include <list>
//测试std::optional 和rvo nrvo

int partition(int arr[], int left, int right)  //找基准数 划分
{
    int i = left;
    int j = right;
    int temp = arr[left];
    while (i <= j)
    {
        while (arr[j] > temp && j >= i)
        {
            j--;
        }
        arr[left] = arr[j];
        while (arr[i] < temp && i <= j)
        {
            i++;
        }
        arr[j] = arr[i];
    }
    swap(arr[j], arr[left]);
    return j;
}
void quick_sort(int arr[], int left, int right)
{
    if (left > right)
    {
        return;
    }
    int j = partition(arr, left, right);
    quick_sort(arr, left, j - 1);
    quick_sort(arr, j + 1, right);
}
 std::vector<int> get_vec_one();

#endif // __TEST_STD_H__
