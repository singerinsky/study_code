#pragma once
#include "../header.h"


class ClassTestForeach
{ 
public:   
    ~ClassTestForeach()
    {
        LOG(INFO)<<"desc......";
    }
    int value = 0;
};

TEST(Test_FOREACH,Test_1)
{
    auto* p = new ClassTestForeach();
    p->value = 4;

    std::map<int,std::unique_ptr<ClassTestForeach>> test_map;

    for(int i =0;i<5;i++)
    {
        auto temp_ptr = std::make_unique<ClassTestForeach>();
        temp_ptr->value = i*i;
        test_map.emplace(i,std::move(temp_ptr));
    }  

    for_each(test_map.begin(),test_map.end(),[&](auto& kv){
        LOG(INFO)<<typeid(kv).name();
        if(kv.second->value == p->value)
        {
            p->value = 1000;
        }
    });

    std::map<int,std::unique_ptr<ClassTestForeach>>::iterator itr = test_map.find(1);
    LOG(INFO) << typeid(itr).name();
    int value = itr->first;

    LOG(INFO)<<"NOW VALUE "<<p->value;
    ASSERT_TRUE(true);
}

TEST(Test_FOREACH,Test_2)
{
    std::vector<ClassTestForeach> all_vec;
    for(int i = 0;i < 10;i++){
        ClassTestForeach p ;
        p.value = i;
        all_vec.push_back(p);
    }
    LOG(INFO) << ".......................................";
    for_each(all_vec.begin(), all_vec.end(), [](const auto &itr)
             {
       LOG(INFO)<<typeid(itr).name();
       LOG(INFO)<<(itr).value; });
    ASSERT_TRUE(true);
}

TEST(Test_FOREACH,Test_3)
{
    std::map<int,int> value = {{2,3},{1,32}};

    for(auto var : value)
    {
       LOG(INFO)<<var.first; 
    }
 
    for(auto& var : value)
    {
       LOG(INFO)<<var.first; 
    }

    for_each(value.begin(),value.end(),[](auto& itr){
        LOG(INFO)<<itr.first<<":"<<itr.second;
        itr.second = 0;
    });
    for_each(value.begin(),value.end(),[](auto itr){
        LOG(INFO)<<itr.first<<":"<<itr.second;
        itr.second = 0;
    });
 
             
}

TEST(Test_FOREACH,Test_iterator)
{
    std::vector<int> vec ={1,2,3,4,5,5};
    std::vector<int>::iterator itr_orgin = vec.begin();
    int i = *itr_orgin;
    auto itr_1 = vec.begin();
    auto itr_2 = itr_1;
    itr_1++;
    LOG(INFO)<<*itr_1<<":"<<*itr_2;
}
