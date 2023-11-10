#ifndef A13B142C_9108_4EA0_8FA3_F19BD41B1172
#define A13B142C_9108_4EA0_8FA3_F19BD41B1172

#include "../header.h"
#include "../util/class_sample.h"
#include <array>
#include <type_traits>

template <typename R, typename P1> R function_template(P1 p) {
  LOG(INFO) << "call function with R template";
  R t;
  return t;
}

template <typename P1> void function_template(P1 p) {
  LOG(INFO) << "call common param function";
}

template <typename P1> void function_template(P1 &p) {
  LOG(INFO) << "call common param function";
}

inline void function_template(float &i) {}

inline void fuction_template(float i) {}

template <> inline void function_template<float>(float i) {
  LOG(INFO) << "call float param function";
}

template <> inline void function_template<void, float>(float i) {
  LOG(INFO) << "call float void ,param function";
}

template <class T, class P> class TemplateClass {};

template <class T> class TemplateClass<int, T>
{
public:
    const std::string name = "int with ";
};

inline void test_void_call() { return function_template(1.0f); }

inline void same_call(int *i) {}

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

template <> inline void do_fill<1>(std::vector<int> &vec) { vec.push_back(0); }

inline void test_call(int *p) {}

inline void test_call(float *p) {}

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

inline void call_function(SampleClass &&object) {
  LOG(INFO) << "calll sampleclass &&";
  LOG(INFO) << object.GetId();
}

template <typename T, typename... Args>
void call_function(T&& t, Args&& ...args)
{
    LOG(INFO) << t;
    call_function(std::forward<Args>(args)...);
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

template <> inline void function_print(const std::string &str) {
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

#endif /* A13B142C_9108_4EA0_8FA3_F19BD41B1172 */
