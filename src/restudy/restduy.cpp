#include "../header.h"
#include <algorithm>
#include <glog/logging.h>
#include <memory>
#include <optional>
#include <type_traits>
#include <typeinfo>
#include <random>


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

