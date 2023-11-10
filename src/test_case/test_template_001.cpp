#include "../../common_lib/lib_header.h"
#include "../header.h"
#include "test_template.h"

TEST(Test_template, split_d) {
  std::string name = "xxxx";
  test_split_define(name);
  test_reachable();
}