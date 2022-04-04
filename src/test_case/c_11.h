#pragma once

#include "gtest/gtest.h"
#include <map>

using namespace std;
class ClassForTest
{

	public:
    ClassForTest(const ClassForTest& test){
		printf("Copc ClassForTest...\n");
    }
    ClassForTest(){
		printf("Consc ClassForTest...\n");
	}

	~ClassForTest(){
		printf("Desc ClassForTest...\n");
	}
	int i = 11;
};



int add(int a,int b){
    return a+b;
}
TEST(FirstTest,test1){
    ASSERT_EQ(add(2,3),5);
}

TEST(SecondTest,test2){
    ASSERT_EQ(add(-2,3),5);
}

TEST(MapTest,test1)
{
    std::map<int,ClassForTest> test_map;
    test_map[1] = ClassForTest();
    test_map[2] = ClassForTest();
    test_map[3] = ClassForTest();
    test_map[4] = ClassForTest();
    std::cout<<"........................."<<endl;
    for(auto&& kv:test_map)
    {
        std::cout<<"-------------in loop"<<endl;
    }

    ASSERT_EQ(test_map.size(),4);
}
