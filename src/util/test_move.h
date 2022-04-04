#pragma once
#include "gtest/gtest.h"
#include "../util/class_sample.h"
#include "../header.h"

enum eSysStatus
{
    eSys_Visible_Flag   = 1,
    eSys_Lock_Flag      = 1<<1,
    eSys_Client_Show_Flag = eSys_Lock_Flag << 1,
};

class ClassShared
{
    public:
        int id = 0;
        ClassShared()
        {
            LOG(INFO)<<"构造 ClassShared";
        }    
        ~ClassShared()
        {
            LOG(INFO)<<"析构 ClassShared"<<id;
        }
};

class ClassMove
{
public:
    std::shared_ptr<ClassShared> shared_;
    int i = 0;
    std::string name ="1111";
};

template<typename T>
void template_function(T t)
{
    LOG(INFO)<<t;
}

template<>
void template_function<int>(int t)
{
    LOG(INFO)<<"int type";
}


TEST(BaseTest,Move)
{
    ASSERT_EQ(eSys_Client_Show_Flag,0x04);
}

TEST(BaseTest,MoveShare)
{
    ClassMove move1;
    move1.shared_ = std::make_shared<ClassShared>();
    move1.shared_->id = 1;
    ClassMove move2;
    move2.shared_ = std::make_shared<ClassShared>();
    move2.shared_->id = 2;
    move1 = move2;
    LOG(INFO)<<"after value copy! ";
    ASSERT_EQ(move1.shared_->id,move2.shared_->id);
}


TEST(BaseTest,EmplaceTest)
{
    ClassMove move1;
    move1.shared_ = std::make_shared<ClassShared>();
    move1.shared_->id = 1;
    std::map<int,ClassMove> test_map;
    std::vector<ClassMove > vec;
    vec.push_back(move1);
    test_map.emplace(1,move1);
    LOG(INFO)<<"current shared_ptr count: "<<move1.shared_.use_count();
    template_function(1);

    auto p = std::make_shared<ClassMove>();
    std::map<int,std::shared_ptr<ClassMove> > map_1;
    {
        std::vector<std::shared_ptr<ClassMove> > vec1;
        vec1.push_back(p);
    }
    map_1.emplace(1,p);
    LOG(INFO)<<"after value copy! "<<p->name;
}

TEST(BaseTest,ConstTest)
{
    constexpr int intsize = sizeof(int*);
    constexpr int charsize = sizeof(char*);
    static_assert(intsize == charsize);
}

TEST(BaseTest,Test_Rest)
{
    auto p = std::make_shared<ClassShared>();
    //auto p1 = std::make_shared<ClassShared>(new ClassShared());
    //auto p1 = p.
    if(p)
    {
        LOG(INFO)<<"p still exist";
    }
    p.reset();
    LOG(INFO)<<"After unique_ptr reset";
    if(p)
    {
        LOG(INFO)<<"p1 still exist";
    }

    auto new_p = new ClassShared;
    p.reset(new_p);

    if(p)
    {
        LOG(INFO)<<"new_p still exist";
    }

    ASSERT_TRUE(true);
}

class ClassWithIntUniquePtr
{
public:
    std::unique_ptr<int> value_ptr ;
    ClassWithIntUniquePtr() {};
    // ClassWithIntUniquePtr(ClassWithIntUniquePtr &&src)
    // {
    // value_ptr = std::make_unique<int>(111);
    // LOG(INFO)<<"call copy.............."<<*(value_ptr);
    // }

    //  ClassWithIntUniquePtr& operator = (const ClassWithIntUniquePtr&& src)
    // {
    //     //value_ptr = std::make_unique<int>(src.value_ptr.get())
    //     return *this;
    // }


    // ClassWithIntUniquePtr& operator = (const ClassWithIntUniquePtr& src)
    // {
    //     return *this;
    // }



};
TEST(BaseTest,test_class_impl_function)
{
    // ClassWithIntUniquePtr p1;
    // ClassWithIntUniquePtr p2;
    // p2 = std::move(p1);
    // ClassWithIntUniquePtr p3(std::move(p1));
    LOG(INFO)<<"移动构造函数 "<<std::is_trivially_constructible<ClassWithIntUniquePtr>::value;
    LOG(INFO)<<"移动构造函数 "<<std::is_move_constructible<ClassWithIntUniquePtr>::value;
    LOG(INFO)<<"移动赋值函数 "<<std::is_move_assignable<ClassWithIntUniquePtr>::value;
}


TEST(BaseTest,test_class_with_up)
{
    ClassWithIntUniquePtr ptr1;

 //   ClassWithIntUniquePtr ptr2;
 //   ptr1 = std::move(ptr2);
    //ptr1.value_ptr = std::make_unique<int>();
//    ClassWithIntUniquePtr* p = new ClassWithIntUniquePtr(std::move(ptr1));
}

class ClassDesSleep
{
public:
    ClassDesSleep()
    {
        static int init = 1;
        age = init;
        init++;
    }
    ~ClassDesSleep()
    {
        sleep(1);
        LOG(INFO)<<"descontruct class !"<<age;
    }
    int age = 0;
    int* get_value(){
        LOG(INFO)<<"call get value";
        return &age;
    }
    const int* get_value()const
    {
        LOG(INFO)<<"call const get value";
        return const_cast<ClassDesSleep*>(this)->get_value();
    }
};

ClassDesSleep get_sleep_object()
{
    ClassDesSleep object;
    return object;
}

template<typename T>
void test_forward(T&& value)
{
   test_forward_call(std::forward<T>(value));
   //test_forward_call(value);
}

template<class T>
void test_forward_call(T&& value)
{
}

template<class T>
void test_forward_call(T& value)
{
}
TEST(BaseTest,test_class_forward)
{
    ClassWithUniquePtr pod;
    test_forward<>(std::move(pod));
    test_forward<ClassWithUniquePtr&>(pod);
}

TEST(BaseTest,test_class_with_desc_sleep)
{
    LOG(INFO)<<"1.start call without object left";
    get_sleep_object();
    LOG(INFO)<<"1.after call without object left";

    LOG(INFO)<<"2.start call with object left";
    const auto& ref = get_sleep_object();
    LOG(INFO)<<"2.after call with object left";

    LOG(INFO)<<"3.start call with new object left";
    auto object= get_sleep_object();
    LOG(INFO)<<"3.after call with new object left";
    int* pvalue = object.get_value();
    const int* const_pvalue = object.get_value();
    const ClassDesSleep* p_class = &object;
    p_class->get_value();
}

const char* test_str_1()
{
    string s1 = string("string1");
    s1.append("s1");
    string s2 = string("string2");
    s2.append("s2");
    const char *p1 = s1.substr(1).data(); // substr(1)的意思是取字符串从下标1到结尾的部分
    string s4 = string("sssss");
    const char *p2 = s2.substr(1).data();
    return p2;
}

TEST(BaseTest,test_str){
    const char* p2 = test_str_1();
    LOG(INFO)<<p2;
}