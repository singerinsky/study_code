#pragma once

#include "../header.h"
#include "../util/class_sample.h"

void static_call()
{
    static auto* p = new SampleClass;
    //delete p;
    LOG(INFO)<<"point address "<<p;
}

TEST(Test_Static,test_1)
{    
    for(int i =0 ;i < 10;i++)
    {
        static_call();
    }
    ASSERT_TRUE(true);
}