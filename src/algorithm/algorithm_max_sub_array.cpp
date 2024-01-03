
#include "gtest/gtest.h"
#include <algorithm>
#include <functional>
#include <glog/logging.h>
#include <vector>

int algorithm_get_max_sub_array(std::vector<int> nums) {
  std::vector<int> dp_array;
  dp_array.resize(nums.size());

  dp_array[0] = nums[0];
  for (int i = 1; i < nums.size(); i++) {
    dp_array[i] = std::max(dp_array[i - 1] + nums[i], nums[i]);
  }

  std::make_heap(dp_array.begin(), dp_array.end(), std::less<int>());
  for (auto &itr : dp_array) {
    LOG(INFO) << itr;
  }
  return dp_array[0];
}

TEST(AlgorithmTest, test_max_sub_array) {
  LOG(INFO) << algorithm_get_max_sub_array(
      std::vector<int>{1, 2, 3, -40, 5, 6, -7, 8, 9, -10});
}
