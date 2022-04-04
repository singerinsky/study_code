/*
 * @file: 
 * @copyright: 2012 - 2028 ByteDance. All Rights Reserved
 * @Author: guanlei
 * @Date: 2021-11-09 10:04:27
 * @brief: 
 */
#pragma once
#include "gtest/gtest.h"

#include "../wsstackrecorder.h"
#include "../shmmgr.h"


void test_stack1()
{
    WS_STACK_TRACK_ENQUEUE
    std::cout<<"call test_stack1"<<endl;
    assert(false);
}

void test_stack2()
{
    test_stack1();
    WS_STACK_TRACK_ENQUEUE
    std::cout<<"call test_stack2"<<endl;
}


TEST(StackTest,test1){
    WS_STACK_TRACK_ENQUEUE
    test_stack2();
    std::cout<<"call StackTest"<<endl;
    ASSERT_EQ(true,true);
}

void function_call(int index_dep,int& dep_rst)
{
    dep_rst++;
    LOG(INFO)<<"......"<<dep_rst<<" index_dep "<<index_dep;
    if(index_dep == 2 || index_dep == 1 || index_dep == 0)
        return;
    function_call(index_dep/2,dep_rst);
}

TEST(StackTest,test_function_1)
{
    int dep_length = 0;
    function_call(100,dep_length);
    LOG(INFO)<<"value 100 with dep :"<<dep_length;
}
