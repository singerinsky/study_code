#include "../header.h"
#include <algorithm>
#include <glog/logging.h>
#include <memory>
#include <optional>
#include <type_traits>
#include <typeinfo>
#include <random>
#include <malloc.h>
#include <stdio.h>
#include "mm_malloc.h"

void restudy_scope_class_function()
{
    struct __struct_tmp_
    {
        ~__struct_tmp_()
        {
            LOG(INFO) << "release scope class!";
        }
    } scope_object;
}


TEST(Test_restudy, restudy_scope_class_function)
{
    restudy_scope_class_function();
}

TEST(Test_restudy, restudy_unique_ptr_test)
{
    std::string str_buff = "hello world";
    std::string target;
    auto ptr = std::make_unique<std::string>();
    *ptr = "to unique";
    ptr.reset();
    if (ptr)
    {
        LOG(INFO) << "from unique" << ptr->c_str();
    }
    else
    {
        LOG(INFO) << "ptr is empty" ;
    }
    target = std::move(str_buff);
    LOG(INFO) << "Source" << str_buff;
    LOG(INFO) << "Created" << target;
}

//测试随机邀请
TEST(Test_restudy, restudy_random_engine)
{
    std::default_random_engine generator;
    constexpr int minx = 1;
    constexpr int maxx = 2000000;
    std::uniform_int_distribution<int> dist(minx, maxx);
    for (int i = 0; i < 100; ++i)
    {
        LOG(INFO)  << dist(generator);
    }

    std::uniform_real_distribution<float> floatDist(0.1f, 1.0f);
    for (int i = 0; i < 100; ++i)
    {
        LOG(INFO)  << floatDist(generator);
    }
}


extern std::optional<std::string> get_ref_optional(bool param = true);


//测试 nullopt
TEST(Test_restudy, restudy_null_opt)
{
    auto rst = get_ref_optional(false);
    if (rst == nullopt)
    {
        LOG(INFO) << " null object";
    }

    rst = get_ref_optional(true);
    if (rst != nullopt)
    {
        LOG(INFO) << "not null object";
    }
}

TEST(Test_restudy, restudy_get_cxx_version)
{
    LOG(INFO) << __cplusplus;
}

TEST(Test_restudy, test_brk)
{
    char* ptr;
    char* start = (char*)sbrk(0);
    printf("Changing allocation with brk() %p\n", start);
    ptr = (char*)malloc(64);
    char* after = (char*)sbrk(0);
    printf("new size%p\n", after - ptr);
    printf("Before brk() call: %p bytes free\n", after);
}

TEST(Test_restudy, test_sbrk)
{
    void* tret;
    char* pmem;
    int i;
    long sbrkret;

    pmem = (char*)malloc(32);
    if (pmem == NULL)
    {
        perror("malloc");
        exit (EXIT_FAILURE);
    }


    printf ("pmem:%p\n", pmem);

    for (i = 0; i < 65; i++)
    {
        sbrk(1);
        printf ("%d\n", (char*)sbrk(0) - (long)pmem - 0x20ff8);   //0x20ff8 就是堆和 bss段 之间的空隙常数；改变后要用 sbrk(0) 再次获取更新后的program break位置
    }
    free(pmem);
}
#include "../util/class_sample.h"
std::optional<SampleClass> get_sample_object()
{
    SampleClass sample_class(1);
    if (sample_class.GetId() == 1)
    {
        return {sample_class};
    }
    else
    {
        return nullopt;
    }
}

TEST(Test_restudy, test_optional)
{
    auto optional_object = get_sample_object();
    if (optional_object == nullopt)
    {
        LOG(INFO) << "null opt";
    }
    std::unique_ptr<SampleClass> object(new SampleClass());
    std::unique_ptr<SampleClass> object_make = std::make_unique<SampleClass>(1);
    if (object)
    {
        LOG(INFO) << "object unique ptr is not null";
    }
    if (object_make)
    {
        LOG(INFO) << "object_make unique ptr is not null";
    }
}