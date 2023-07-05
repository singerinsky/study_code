#include "../header.h"
#include <algorithm>
#include <type_traits>
#include <typeinfo>

void foo(char *) { std::cout << "foo(char*) is called" << std::endl; }
void foo(int i) { std::cout << "foo(int) is called" << std::endl; }

TEST(Test_std20, test001) {
  auto x = nullptr;
  if (std::is_same<decltype(NULL), decltype(0)>::value)
    std::cout << "NULL == 0" << std::endl;
  if (std::is_same<decltype(NULL), decltype((void *)0)>::value)
    std::cout << "NULL == (void *)0" << std::endl;
  if (std::is_same<decltype(x), std::nullptr_t>::value)
    std::cout << "NULL == nullptr" << std::endl;

  foo(0); // 调用 foo(int)
  // foo(NULL);    // 该行不能通过编译
  foo(nullptr); // 调用 foo(char*)
}

template <typename... Ts> void magic(Ts... args) {
  LOG(INFO) << sizeof...(args) << std::endl;
}

TEST(Test_std20, test002) { magic(1, 0.1F, "SSS"); }
