#pragma once
#include "../header.h"
#include "../util/class_sample.h"

TEST(Test_Array, test_1) {
  std::array<std::unique_ptr<SampleClass>, 10> class_array;
  class_array[0] = std::make_unique<SampleClass>();
  auto ptr = std::make_unique<SampleClass>();
  class_array[1] = std::forward<std::unique_ptr<SampleClass>>(
      std::make_unique<SampleClass>());
  // std::set<0>(std::make_unique<SampleClass>());
  ASSERT_TRUE(true);
}

TEST(Test_Array, test_2) {
  std::array<std::shared_ptr<SampleClass>, 10> class_array;
  class_array.fill(std::make_shared<SampleClass>());
  for_each(class_array.begin(), class_array.end(), [](auto &ele) {
    LOG(INFO) << "will ele ref count will be " << ele.use_count();
  });
  auto &ptr = std::get<0>(class_array);
  for_each(class_array.begin(), class_array.end(), [](auto ele) {
    LOG(INFO) << "will ele ref count will be " << ele.use_count();
  });

  std::hash<std::string> str_hash;
  auto hash_valuie = str_hash("name");
  std::unordered_map<std::string, std::string> _hash_map;
  _hash_map.insert(std::make_pair("14", "3"));
  auto itr = _hash_map.find("14");
  ASSERT_TRUE(true);
}

TEST(Test_Hash, test_2) {
  std::hash<int> int_hash;
  auto hash_value1 = int_hash(1);
  auto hash_value2 = int_hash(100000000);
  LOG(INFO) << "hash value1 " << hash_value1 << " hash_value2 " << hash_value2;
  std::hash<std::string> str_hash;
  auto str_hash_1 =
      str_hash("guanleiguanleiguanleiguanleiguanleiguanleiguanlei");
  auto str_hash_2 =
      str_hash("guanleiguanleiguanleiguanleiguanleiguanleiguanlei");

  std::hash<float> float_hash;
  auto float_hash1 = float_hash(51.0f);
  auto float_hash2 = float_hash(51.0f);
  LOG(INFO) << "hash value1 " << float_hash1 << " hash_value2 " << float_hash2;
  ASSERT_TRUE(true);
}

int g_value = 1;

int get_value() { return 3; }

void test_default_param(int value, int defalut_value = get_value()) {
  LOG(INFO) << defalut_value;
}

TEST(TestBase, g_default_test) {
  test_default_param(1);
  g_value = 2;
  test_default_param(1);
}