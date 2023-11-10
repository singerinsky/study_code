#include "test_template.h"
#include "../header.h"

template <typename T> void test_bool_and_int(T t) {
  if (std::is_same<T, bool>::value) {
    LOG(INFO) << "Testing bool";
  } else if (std::is_same<T, int>::value) {
    LOG(INFO) << "Testing int";
  } else {
    LOG(INFO) << "Testing unknown type";
  }
}

TEST(Test_template, test_bool_and_int) {
  test_bool_and_int(true);
  test_bool_and_int(0);
  test_bool_and_int(std::string("test"));
  const std::string &&str = std::string("test");
  LOG(INFO) << "Testing is_rvalue_reference"
            << std::is_rvalue_reference<decltype(str)>::value;
}

TEST(Test_template, test_01) {
  int i = 0;
  TemplateClass<int, double> new_class;
  class_i_d new_class_1;
  //    function_template<char>(c);
}

TEST(Test_template, test_02) {
  template_func_with_size<int, 10>();
  template_func_with_size_and_call<int, 100, function_<int>>();
  LOG(INFO) << SingletonClassOne::Instance();
  LOG(INFO) << SingletonClassTwo::Instance();
}
TEST(Test_template, test_03) {
  std::vector<int> vec;
  // do_fill<100>(vec);
  do_fill(vec);
  for (auto itr : vec) {
    LOG(INFO) << itr;
  }
  for_each(vec.begin(), vec.end(), [](auto &itr) { LOG(INFO) << itr; });

  ClassWithTemplateFunction function_object;
  int *pint = new int;
  float *pfloat = new float;

  function_object.call<int, test_call>(pint);
  function_object.call<float, test_call>(pfloat);
}
TEST(TestTemplate, args_call) {
  int i = 1;
  float j = 2.f;
  SampleClass object{3};
  call_function(i, j, std::move(object));
  // call_function(i,j,object);
  // call_function(object);
}
TEST(TestTemplate, stl_t) {
  std::vector<int> vec = {1, 2, 34, 4};
  function_print(vec);
  int i = 0;
  function_print(i);
  std::string str = "....";
  function_print(str);
  std::vector<std::string> vec_str = {"111", "222"};
  function_print(vec_str);
}

TEST(TestTemplate, type_traits_001) {
  auto purposeint = 1;
  auto rst = TypeJustice<decltype(purposeint)>::is_int_value();
  LOG(INFO) << "type is int" << rst;
}
