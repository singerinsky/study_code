#include "../header.h"
#include "../util/HashMap.h"
#include <gtest/gtest.h>
#include <string>

using namespace guanlei;
TEST(test_stl, test_open_hash_map) {
  guanlei::HashMap<std::string, std::string> map_one(10, "guanlei");
  map_one["guanlei"] = "guanlei";
  LOG(INFO) << map_one.bucket_count();
  LOG(INFO) << map_one.size();
}