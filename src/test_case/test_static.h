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
    auto t1 = std::async(std::launch::async, []() {
                         LOG(INFO)<<"Start t1 get instance";
                         auto p = SingleClass::Instance(10);
                         if(p){
                         LOG(INFO)<<"t1 GET instance not null"<<p;
                         }
                         });
    sleep(5);
    auto t2 = std::async(std::launch::async, []() {
                         LOG(INFO)<<"Start t2 get instance";
                         auto p = SingleClass::Instance(1);
                         if(p){
                         LOG(INFO)<<"t2 GET instance not null"<<p;
                         }
                         });
    LOG(INFO)<<"END";
}

TEST(Test_Static,test_singleton_template)
{    
    auto t1 = std::async(std::launch::async, []() {
                         LOG(INFO)<<"Start t1 get instance";
                         auto& p = SingletonClassTemplate<int>::GetInstance();
                         LOG(INFO)<<"t1 GET instance not null"<<&p;
                         });

    sleep(2);
    auto t2 = std::async(std::launch::async, []() {
                         LOG(INFO)<<"Start t2 get instance";
                         auto& p = SingletonClassTemplate<int>::GetInstance();
                         LOG(INFO)<<"t2 GET instance not null"<<&p;
                         });

    LOG(INFO)<<"begin another instance type";
    auto t3 = std::async(std::launch::async, []() {
                         LOG(INFO)<<"Start t3 get instance";
                         auto& p = SingletonClassTemplate<double>::GetInstance();
                         LOG(INFO)<<"t3 GET instance not null"<<&p;
                         });
    LOG(INFO)<<"END";
}
