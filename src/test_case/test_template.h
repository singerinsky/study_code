#ifndef A13B142C_9108_4EA0_8FA3_F19BD41B1172
#define A13B142C_9108_4EA0_8FA3_F19BD41B1172

#include "../header.h"
#include <array>
#include "../util/class_sample.h"
#include <type_traits>

template <typename R, typename P1> R function_template(P1 p)
{
    LOG(INFO) << "call function with R template";
    R t;
    return t;
}

template <typename P1> void function_template(P1 p)
{
    LOG(INFO) << "call common param function";
}

template <typename P1> void function_template(P1& p)
{
    LOG(INFO) << "call common param function";
}

void function_template(float& i) {}

void fuction_template(float i) {}

template <> void function_template<float>(float i)
{
    LOG(INFO) << "call float param function";
}

template <> void function_template<void, float>(float i)
{
    LOG(INFO) << "call float void ,param function";
}

template <class T, class P> class TemplateClass {};

template <class T> class TemplateClass<int, T>
{
public:
    const std::string name = "int with ";
};

void test_void_call()
{
    return function_template(1.0f);
}

void same_call(int* i) {}

template <class T, int size> void template_func_with_size()
{
    std::array<T, size> array;
    LOG(INFO) << "array size is " << array.size();
}

template <class T, int size, void (*F)(T&)>
void template_func_with_size_and_call()
{
    std::array<T, size> array;
    array.fill(10);
    for (auto ele : array)
    {
        F(ele);
    }
    LOG(INFO) << "array size is " << array.size();
}

template <typename T> void function_(T& t)
{
    LOG(INFO) << t + 1;
}

// template class TemplateClass<int,double>;
typedef TemplateClass<int, double> class_i_d;

template <class T> void do_fill(std::vector<T>& vec);

template <int i = 100> void do_fill(std::vector<int>& vec)
{
    vec.push_back(i);
    do_fill < i - 1 > (vec);
}

template <> void do_fill<1>(std::vector<int>& vec)
{
    vec.push_back(0);
}

TEST(Test_template, test_01)
{
    int i = 0;
    TemplateClass<int, double> new_class;
    class_i_d new_class_1;
    //    function_template<char>(c);
}

TEST(Test_template, test_02)
{
    template_func_with_size<int, 10>();
    template_func_with_size_and_call<int, 100, function_<int>>();
    LOG(INFO) << SingletonClassOne::Instance();
    LOG(INFO) << SingletonClassTwo::Instance();
}

void test_call(int* p) {}

void test_call(float* p) {}

TEST(Test_template, test_03)
{
    std::vector<int> vec;
    // do_fill<100>(vec);
    do_fill(vec);
    for (auto itr : vec)
    {
        LOG(INFO) << itr;
    }
    for_each(vec.begin(), vec.end(), [](auto & itr)
    {
        LOG(INFO) << itr;
    });

    ClassWithTemplateFunction function_object;
    int* pint = new int;
    float* pfloat = new float;

    function_object.call<int, test_call>(pint);
    function_object.call<float, test_call>(pfloat);
}

template <class T> void call_function(T&& t)
{
    LOG(INFO) << "calll &&";
    if (is_lvalue_reference<decltype(t)>::value == 1)
    {
        LOG(INFO) << "ture";
    }
    else if (is_rvalue_reference<decltype(t)>::value == 1)
    {
        LOG(INFO) << "false";
    }
}

// void call_function(SampleClass& object)
// {
//     LOG(INFO)<<"calll sampleclass &";
//     LOG(INFO)<<object.GetId();
// }

void call_function(SampleClass&& object)
{
    LOG(INFO) << "calll sampleclass &&";
    LOG(INFO) << object.GetId();
}

template <typename T, typename... Args>
void call_function(T&& t, Args&& ...args)
{
    LOG(INFO) << t;
    call_function(std::forward<Args>(args)...);
}

TEST(TestTemplate, args_call)
{
    int i = 1;
    float j = 2.f;
    SampleClass object{3};
    call_function(i, j, std::move(object));
    // call_function(i,j,object);
    // call_function(object);
}

// template <class T> void function_print(T &t) {
//   std::string str = std::to_string(t);
//   LOG(INFO) << str;
// }
template <class T> void function_print(const T& t)
{
    std::string str = std::to_string(t);
    LOG(INFO) << str;
}

template <class T> void function_print(const T&& t)
{
    std::string str = std::to_string(t);
    LOG(INFO) << str;
}

template <class T> void function_print(std::vector<T>& vec)
{
    for (auto& t : vec)
    {
        function_print(t);
    }
}

template <> void function_print(const std::string& str)
{
    LOG(INFO) << "this is string ";
}

template<typename T>
class TypeJustice
{
public:
    typedef T* TypePoint;
    static constexpr bool is_int_value()
    {
        return   false;
    }
};

template<>
class TypeJustice<int>
{
public:
    typedef int* TypePoint;
    static constexpr bool is_int_value()
    {
        return true;
    }
};

TEST(TestTemplate, stl_t)
{
    std::vector<int> vec = {1, 2, 34, 4};
    function_print(vec);
    int i = 0;
    function_print(i);
    std::string str = "....";
    function_print(str);
    std::vector<std::string> vec_str = {"111", "222"};
    function_print(vec_str);
}

TEST(TestTemplate, type_traits_001)
{
    auto purposeint = 1;
    auto rst = TypeJustice<decltype(purposeint)>::is_int_value();
    LOG(INFO) << "type is int" << rst;

}


#endif /* A13B142C_9108_4EA0_8FA3_F19BD41B1172 */
