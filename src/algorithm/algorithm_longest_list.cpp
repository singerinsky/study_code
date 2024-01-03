#include "../header.h"

int get_longest(const std::vector<int> &nums) {
  std::vector<int> dp(nums.size(), 1);
  std::vector<std::vector<int>> array_content(nums.size());

  for (int i = 0; i < nums.size(); i++) {
    array_content[i].push_back(nums[i]);
  }

  for (int index = 1; index < nums.size(); index++) {
    std::vector<int> tmpVec;
    for (int j = 1; j < index; j++) {
      if (nums[index] >= nums[j]) {
        dp[index] = std::max(dp[index], dp[j] + 1);
        tmpVec.push_back(nums[index]);
      }
    }
    array_content[index].insert(array_content[index].end(), tmpVec.begin(),
                                tmpVec.end());
  }

  int max = 0;
  for (auto itr : dp) {
    if (itr > max) {
      max = itr;
    }
  }

  for (auto &vec : array_content) {
    std::string result;
    for (auto &v : vec) {
      result += v;
      LOG(INFO) << v;
      if (v < vec.size() - 1) {
        result += ", ";
      }
    }
    LOG(INFO) << result;
  }

  return max;
}

TEST(AlgorithmTest, longest_list) {
  LOG(INFO) << get_longest({9, 2, 5, 7, 1, 16, 17, 3});
  LOG(INFO) << "call end!";
}