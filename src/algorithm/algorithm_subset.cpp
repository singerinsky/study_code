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