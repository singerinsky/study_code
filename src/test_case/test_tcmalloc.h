#pragma once
#include "../header.h"
#include "../util/class_sample.h"
#include <gtest/gtest.h>

TEST(Malloc_Test,test1)
{
	void* p  = malloc(1);
	if(p)
    {
        LOG(INFO)<<"MALLOC OK USE GOOGLE";
    }else{
        LOG(INFO)<<"MALLOC FAILED USE GOOGLE";
    }
    ASSERT_TRUE(true);
}

void function_bind(int& value)
{
    value++;
}

void function_class_bind(SampleClass& simple_class)
{
    simple_class.SetId(1000);
}

//bind 默认是传值入参，现在通过std::ref 包装了引用，可以传引用
TEST(Malloc_Test,refTest)
{
    int value = 0;
    auto bind_func = std::bind(function_bind,std::ref(value));
    bind_func();
    LOG(INFO)<<"now value is "<<value;
    SampleClass class_simple;
    auto bind_class_func = std::bind(function_class_bind,std::ref(class_simple));
    bind_class_func();

    std::unique_ptr<int> ptr = std::make_unique<int>();

    
    std::unique_ptr<int> ptr1 = nullptr;
    if(ptr1){
        LOG(INFO)<<"not null";
    }else{
        LOG(INFO)<<"null ";
    }
    //ASSERT_EQ(ptr,nullptr);
    //ASSERT_EQ(class_simple.GetId(),1000);
}


class ObjectTest:public testing::Test{

};