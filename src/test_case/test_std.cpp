#include "test_std.h"
#include "../header.h"
#include <functional>
#include <initializer_list>
#include <mutex>
#include <type_traits>
#include <typeinfo>

TEST(BaseTest, test_std_parition) {
  std::vector<int> vec_value = {1, 2, 34, 4, 5, 6, 7};
  std::partition(vec_value.begin(), vec_value.end(),
                 [](const auto &itr) { return itr >= 5; });
  for_each(vec_value.begin(), vec_value.end(),
           [](auto &itr) { LOG(INFO) << itr; });
}

TEST(BaseTest, test_std_string) {
  std::string name = "123456789";
  name = "123";
  name.reserve(1);
  LOG(INFO) << name;
}

TEST(BaseTest, test_mstime) {
  long long ms = ustime();
  LOG(INFO) << ms;
}

TEST(BaseTest, test_initlizelist) {
  SampleClass object{1};
  std::string str_sample = "sample";
  function_params(1, "string", str_sample, 3, 4, 5, 6, std::move(object));
}

TEST(BaseTest, scope_test) {
  // scope_class_function();
  int i = 0;
  test_right(i);
  test_right_1(1);
  float j = 1.0f;
  float &ref = j;
  test_right_1(ref);
  LOG(INFO) << ref;
}

#include <list>
//测试std::optional 和rvo nrvo
TEST(BaseTest, test_ref_return) {
  std::string ref = std::move(get_ref_string());
  const std::string &const_ref = get_ref_string();
  auto rst = get_ref_optional();

  //    const SampleClass& object = get_sample_class();

  // rvo 优化
  { SampleClass object_rvo = get_sample_class_with_rvo(); }
  LOG(INFO) << "...................................with nrvo";
  //直接nrvo优化
  { SampleClass object = get_sample_class_with_nrvo(); }
  LOG(INFO) << "...................................";
  { SampleClass object1 = get_sample_class_without_nrvo(); }
  LOG(INFO) << "...................................";
  {
    // decltype(SampleClass())::value_type t;
  }
  LOG(INFO) << "................................... with rvo";
  ClassWithFunctionReturnObject object;
  SampleClass object_return = object.GetObject();
  std::queue<int, std::list<int>> queue_int;
}

void my_terminate() {
  LOG(INFO) << "my_terminate called" << std::endl;
  std::abort();
}

TEST(BaseTest, test_terminate) {
  std::set_terminate(my_terminate);
  throw std::exception();
  try {
    throw std::exception();
  } catch (const std::exception &e) {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
}

TEST(BaseTest, test_remove) {
  std::list<int> vec = {1, 2, 3};
  vec.remove(1);
}

class Bank {
private:
  double money = 999'999'999;

public:
  void check() { std::cout << "check:" << money << "\n"; }
};

template <auto M> struct Tunnel;

template <class T, class U, T U::*M> struct Tunnel<M> {
  friend T &sneak(U &u) { return u.*M; }
};

template struct Tunnel<&Bank::money>;
double &sneak(Bank &);

TEST(BaseTest, test_p) {
  Bank bank;
  bank.check();

  auto &take_control = sneak(bank);
  auto booty = take_control;
  take_control = 0.114514;
  std::cout << "booty: " << booty << "\n";

  bank.check();
}

template <auto T> class auto_class {
public:
  typedef decltype(T) value_type;
  decltype(T) *t;
};

TEST(BaseTest, test_p1) {
  auto_class<1> class1;
  auto_class<1>::value_type t = 111;
  LOG(INFO) << typeid(auto_class<1>::value_type).name();
  LOG(INFO) << std::string(10, ' ') << "end";
}

template <typename T>
typename std::enable_if<std::is_integral<T>::value == true, void>::type
print_internal(T value, size_t indent = 0,
               const std::string &line_terminator = "\n", size_t level = 0) {
  LOG(INFO) << value;
}

template <typename T>
typename std::enable_if<std::is_function<T>::value == true, void>::type
print_internal(T value, size_t indent = 0,
               const std::string &line_terminator = "\n", size_t level = 0) {
  value();
}

template <typename T>
typename std::enable_if<std::is_pointer<T>::value == true, int>::type
print_internal(T value, size_t indent = 0,
               const std::string &line_terminator = "\n", size_t level = 0) {
  LOG(INFO) << value;
  return 1;
}

// 示例函数
void myFunction() { std::cout << "Hello, world!" << std::endl; }

TEST(BaseTest, test_enable_if) {

  print_internal(1);
  print_internal<decltype(myFunction)>(myFunction);
  LOG(INFO) << typeid(decltype(print_internal((new int())))).name();

  LOG(INFO) << std::string(10, ' ') << "end";
  // 函数无法推导
  //  print_internal(std::function<void()>(myFunction));
}
template <typename... CS> std::string_view char_to_string() { return ""; }

template <char... CS> std::string_view char_to_string() {
  static char p[sizeof...(CS)] = {CS...};
  return std::string_view(p, sizeof...(CS));
}

TEST(BaseTest, test_char_template_to_string) {
  std::string_view str = char_to_string<'a', 'b'>();

  auto func_addr_one = &char_to_string<'a', 'b'>;
  auto func_addr_two = &char_to_string<'a', 'c'>;
  // use LOG(INFO) print func_addr_one and func_addr_two
  LOG(INFO) << func_addr_one << " func_addr_one";
  LOG(INFO) << func_addr_two << " func_addr_two";
  printf("函数地址：%p\n", func_addr_one);
  printf("函数地址：%p\n", func_addr_two);
  LOG(INFO) << str;
  str = char_to_string<1, 2, 3>();
  LOG(INFO) << str;
}

struct HasStdHash {
private:
  template <class T, class Dummy = decltype(std::hash<T>{})>
  static constexpr bool exists(int) {
    return true;
  }

  template <class T> static constexpr bool exists(char) { return false; }

public:
  template <class T> static constexpr bool check() { return exists<T>(43); }
};
TEST(BaseTest, test_check_hash) {
  std::cout << "Does std::string have std::hash? "
            << HasStdHash::check<std::string>() << endl;
  std::cout << "Does std::string_view have std::hash? "
            << HasStdHash::check<std::string_view>();
}

int func_return_int(float fValue) { return 0; }

template <class F, class... Args>
auto print_result(F &&f, Args &&...args) ->
    typename std::result_of<F(Args...)>::type {
  using return_type = typename std::invoke_result<F, Args...>::type;
  LOG(INFO) << typeid(return_type).name();
}

TEST(BaseTest, test_get_return) {
  decltype(print_result(func_return_int, 0.1f)) value;
  value = 1.0f;
  LOG(INFO) << value;
}

std::vector<int> get_vec_one()
{
  return {1};
}

TEST(BaseTest,ref_right){

  auto func = []()->std::vector<int>
  { 
    //std::vector<int> vec= {1};
    //return vec;
    return {1};
  };
  std::vector<int>&& ref_one = get_vec_one();
  std::vector<int>&& ref = func();
  LOG(INFO)<<"xxxx";
  ref.push_back(1);
  //ref_one.push_back(1);
  LOG(INFO)<<ref.size();



  int&& int_ref = 1;
  int_ref = 10;
  LOG(INFO)<<int_ref;
}

class CBaseForPtr{
public:
    virtual void call1(){
        LOG(INFO)<<"base call 1!"<<endl;
    }
    virtual void call2(){
        LOG(INFO)<<"base call 2!"<<endl;
    }
    virtual void call3(){}


};

class CSubForPtr:public CBaseForPtr {
public:
    void call1(){
        LOG(INFO)<<"sub call!"<<endl;
    }
};

TEST(BaseTest,test_ptr)
{
    CBaseForPtr* pBasePtr = new CBaseForPtr();
    long* pFuncPtr = (long*)(*(long*)(pBasePtr));
    for(int i =0;i<4;i++){
        LOG(INFO)<<(pFuncPtr[i]);
    }
    typedef void(*FP)();
    FP* p1 = (FP*)(pFuncPtr + 1);
    (*p1)();

    pBasePtr = new CSubForPtr();
    pFuncPtr = (long*)(*(long*)(pBasePtr));
    for(int i =0;i<4;i++){
        LOG(INFO)<<(pFuncPtr[i]);
    }
    p1 = (FP*)pFuncPtr;
    (*p1)();
}








