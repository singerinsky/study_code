#include "test_std.h"
#include "../header.h"
#include <initializer_list>
#include <mutex>
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
}