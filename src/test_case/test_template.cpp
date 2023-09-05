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