#include "algorithm_subset.h"

TEST(CollectSubSetsTest, NormalTest) {
  std::vector<int> v = {1, 2, 3};
  std::vector<std::vector<int>> res = CollectSubSets(v);

  printVectorOfVectors(res);
  // 检查结果数量
  EXPECT_EQ(res.size(), 8);
  // 检查结果是否包含预期子集
  EXPECT_TRUE(std::find(res.begin(), res.end(), std::vector<int>({1})) !=
              res.end());
  EXPECT_TRUE(std::find(res.begin(), res.end(), std::vector<int>({2})) !=
              res.end());
  EXPECT_TRUE(std::find(res.begin(), res.end(), std::vector<int>({3})) !=
              res.end());
  EXPECT_TRUE(std::find(res.begin(), res.end(), std::vector<int>({1, 2})) !=
              res.end());
  EXPECT_TRUE(std::find(res.begin(), res.end(), std::vector<int>({1, 3})) !=
              res.end());
  EXPECT_TRUE(std::find(res.begin(), res.end(), std::vector<int>({2, 3})) !=
              res.end());
  EXPECT_TRUE(std::find(res.begin(), res.end(), std::vector<int>({1, 2, 3})) !=
              res.end());
  EXPECT_TRUE(std::find(res.begin(), res.end(), std::vector<int>()) !=
              res.end());
}

// 测试 permate 函数
TEST(PermateTest, NormalTest) {
  std::array<int, 4> nums = {1, 2, 3, 4};
  vector<set<int>> expected = {{1, 2, 3}, {1, 2, 4}, {1, 3, 4}, {2, 3, 4}};
  vector<set<int>> res = permate(nums);
  EXPECT_EQ(res, expected);
}

// 测试 permate_track_back 函数
TEST(PermateTrackBackTest, NormalTest) {
  array<int, 4> nums = {1, 2, 3, 4};
  set<int> track;
  vector<set<int>> res;
  permate_track_back(nums, track, res);
  vector<set<int>> expected = {{1, 2, 3}, {1, 2, 4}, {1, 3, 4}, {2, 3, 4}};
  EXPECT_EQ(res, expected);
}