#include "../header.h"
#include <algorithm>
#include <vector>

int countPrime(int nEnd) {
  std::vector<bool> vec;
  vec.assign(nEnd, true);

  for (int i = 2; i < nEnd; i++) {
    if (vec[i]) {
      for (int j = 2 * i; j < nEnd; j += i) {
        vec[j] = false;
      }
    }
  }

  int count = 0;
  for (int i = 2; i < nEnd; i++) {
    if (vec[i]) {
      count++;
    }
  }

  return count;
}
/*
can_finish函数：

函数接受三个参数：vec表示任务的权重向量，d表示天数，cap表示每天的容量。
函数使用一个循环来模拟每一天的处理过程。
在循环中，函数计算当天的最大容量maxcap，并通过减去当天任务的权重来更新maxcap。
如果maxcap大于等于 0，表示当天可以完成至少一个任务，则继续处理下一个任务。
如果完成了所有任务，即i等于任务向量的长度，表示所有任务都可以完成，函数返回true。
如果在处理过程中，maxcap小于 0，表示当天无法完成任何任务，函数返回false。
shipwithdays函数：

函数接受两个参数：vecWeights表示任务的权重向量，b表示可用的天数。
函数首先初始化变量left和sum，用于计算和管理任务的总权重。
函数使用for_each循环遍历任务权重向量，将每个任务的权重传递给find_max_and_get_sum函数。
在find_max_and_get_sum函数中，如果当前任务的权重大于left，则更新left为当前任务的权重。同时，将当前任务的权重加到sum上。
完成遍历后，计算出left和sum的值。
接下来，使用一个循环来进行二分搜索。
循环条件是left小于sum，表示还有未分配的任务权重。
在每次循环迭代中，计算中间值mid，即left和(sum - left) / 2的和。
调用can_finish函数，传入vecWeights、b和mid作为参数，判断在给定天数和容量限制下是否能够完成所有任务。
如果can_finish返回true，表示可以完成任务，将sum更新为mid，并继续进行下一次迭代。
如果can_finish返回false，表示无法完成任务，将left更新为mid +
1，继续进行下一次迭代。
循环结束后，left的值即为在给定天数和容量限制下，能够完成任务的最小总权重。
函数返回left作为结果。*/
bool can_finish(std::vector<int> &vec, int d, int cap) {
  int i = 0;
  for (int day = 0; day < d; day++) {
    int maxcap = cap;
    while ((maxcap -= vec[i]) >= 0) {
      i++;
      if (i == vec.size()) {
        return true;
      }
    }
  }
  return false;
}

int shipwithdays(std::vector<int> vecWeights, int b) {
  int left = 0;
  int sum = 0;
  auto find_max_and_get_sum = [&](int x) {
    if (x > left) {
      left = x;
    }
    sum += x;
  };
  for_each(vecWeights.begin(), vecWeights.end(), find_max_and_get_sum);

  while (left < sum) {
    int mid = left + (sum - left) / 2;
    if (can_finish(vecWeights, b, mid)) {
      sum = mid;
    } else {
      left = mid + 1;
    }
  }
  return left;
}

int trap(std::vector<int> &height) {
  if (height.empty())
    return 0;
  int n = height.size();
  int ans = 0;

  vector<int> l_max(n), r_max(n);
  l_max[0] = height[0];
  r_max[n - 1] = height[n - 1];
  for (int i = 1; i < n; i++) {
    l_max[i] = max(height[i], l_max[i - 1]);
  }
  for (int i = n - 2; i >= 0; i--) {
    r_max[i] = max(height[i], r_max[i + 1]);
  }
  for (int i = 1; i < n - 1; i++) {
    ans += min(l_max[i], r_max[i]) - height[i];
  }

  return ans;
}

std::vector<int> remove_duplicate(std::vector<int> &nums) {
  int slow_index = 0;
  int fast_index = 1;

  while (fast_index < nums.size()) {
    if (nums[slow_index] != nums[fast_index]) {
      slow_index++;
      nums[slow_index] = nums[fast_index];
    }
    fast_index++;
  }
  LOG(INFO) << slow_index;
  return std::vector<int>(nums.begin(), nums.begin() + slow_index + 1);
}

TEST(RemoveDuplicateTest, Basic) {
  std::vector<int> input = {1, 2, 2, 3, 3, 4};
  std::vector<int> expected = {1, 2, 3, 4};

  auto rest = remove_duplicate(input);

  EXPECT_EQ(rest, expected);
}