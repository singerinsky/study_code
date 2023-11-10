#include "../../common_lib/lib_header.h"
#include "../header.h"
#include "test_template.h"

TEST(Test_template, split_d) {
  const std::string name = "xxxx";
  test_split_define(name);
  test_split_define(11);
  test_reachable();
}