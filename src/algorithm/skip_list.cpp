#include "skip_list.h"

TEST(AlgorithmTest, test_skill_list_001) {
  SkipList<int> list;
  list.insert(1);
  list.insert(11);
  list.insert(111);
  list.insert(1111);
  LOG(INFO) << list.contains(111);
}

TEST(AlgorithmTest, test_skill_list_002) {
  SkipList<int> list;
  list.insert(1);
  list.insert(11);
  list.clear();
}