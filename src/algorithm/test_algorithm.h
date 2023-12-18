#ifndef C9C490D2_686C_4343_B8C0_4C24EC0A9CDC
#define C9C490D2_686C_4343_B8C0_4C24EC0A9CDC

#include "../header.h"
//计算所需要的硬币的数量
int calc_coin(std::vector<int> &coin_type, int remain_value);

//生成矩阵
std::vector<std::vector<bool>> generate_mat(int size);

// binary search left bound
template <class T>
int binarySearchLowerBound(std::vector<T> vec, const T &target) {
  if (vec.empty()) {
    return false;
  }
  int left = 0;
  int right = vec.size();
  int mid = 0;
  while (left < right) {
    mid = (left + right) / 2;
    if (vec[mid] == target) {
      right = mid;
    } else if (vec[mid] < target) {
      left = mid + 1;
    } else if (vec[mid] > target) {
      right = mid;
    }
  }
  return left;
}

#endif /* C9C490D2_686C_4343_B8C0_4C24EC0A9CDC */