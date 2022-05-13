#ifndef _TEST_NEW_H_
#define _TEST_NEW_H_
#include "../header.h"
#include "../util/class_sample.h"
#include <gtest/gtest.h>
#include <memory>


TEST(Test_New,Test001)
{
	std::unique_ptr<SampleClass> p = std::make_unique<SampleClass>();
	ClassWithUniquePtr* ptr = new ClassWithUniquePtr();
	ptr->ptr_ = std::move(p);
	ptr->~ClassWithUniquePtr();
	LOG(INFO)<<"after manual call descutor function";
	PodSampleClass* p1 = new SubPodClass;
	PodSampleClass& ref = *p1;

	LOG(INFO)<<typeid(std::remove_pointer<decltype(p1)>::type).name()<<".................";
	LOG(INFO)<<typeid(std::remove_reference<decltype(ref)>::type).name()<<".................";
}

TEST(Test_New,Test002)
{
	PodSampleClass* pclass = new SubPodClass(1,2);
	SubPodClass* subclass = dynamic_cast<SubPodClass*>(pclass);
	LOG(INFO)<<pclass->CheckClass();
	LOG(INFO)<<subclass->CheckClass();
    //delete subclass;
    subclass->IsValied();
}

TEST(Test_New,Test003)
{
	ClassWithData* pobject= new ClassWithData;
	char* pclass = reinterpret_cast<char*>(pobject + 1);
	char* pObjectData = pobject->buff;
	LOG(INFO)<<&pclass<<":"<<&pObjectData;
	ASSERT_EQ(pclass, pObjectData);
}

TEST(Test_New,place_new)
{
    void* p = malloc(sizeof(std::string));
    new(p)(std::string);
    std::string* pstr = static_cast<std::string*>(p);
    *pstr = "1111";
    LOG(INFO)<<*pstr;
}

#endif
