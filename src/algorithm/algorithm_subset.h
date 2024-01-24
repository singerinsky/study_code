#ifndef E3415060_4C34_4B8F_9FBC_02C5149656D8
#define E3415060_4C34_4B8F_9FBC_02C5149656D8
#include "../header.h"
#include <array>
#include <vector>

template <class T>
std::vector<std::vector<T>> CollectSubSets(std::vector<T> &v) {
  if (v.empty()) {
    LOG(INFO) << "empty!";
    return {{}};
  }
  T t = v.back();
  LOG(INFO) << "t: " << t;
  v.pop_back();
  std::vector<std::vector<T>> tmp = CollectSubSets(v);
  size_t vec_num = tmp.size();
  for (int i = 0; i < vec_num; i++) {
    std::vector<T> subset = tmp[i];
    subset.push_back(t);
    tmp.push_back(subset);
  }
  return tmp;
}

template <class T>
void printVectorOfVectors(const std::vector<std::vector<T>> &vec) {
  std::stringstream ss;
  ss << "vec = [";
  for (const auto &innerVec : vec) {
    ss << "[";
    for (const auto &num : innerVec) {
      ss << num << ", ";
    }
    ss.seekp(-2, std::ios_base::end); // 移除最后一个", "
    ss << "], ";
  }
  ss.seekp(-2, std::ios_base::end); // 移除最后一个", "
  ss << "]";
  LOG(INFO) << ss.str();
}

inline void backtrack(int n, int k, int start, vector<int> &track,
                      vector<vector<int>> &res) {
  if (k == track.size()) {
    res.push_back(track);
    return;
  }

  for (int i = start; i <= n; i++) {
    track.push_back(i);
    backtrack(n, k, i + 1, track, res);
    track.pop_back();
  }
}

inline vector<vector<int>> combine(int n, int k) {
  vector<vector<int>> res;
  if (k <= 0 || n <= 0)
    return res;
  vector<int> track;
  backtrack(n, k, 1, track, res);
  return res;
}

template <class T, size_t num_size = 10>
vector<std::set<T>> permate(std::array<T, num_size> &nums) {
  vector<std::set<T>> res;
  std::set<T> track;
  permate_track_back(nums, track, res);
  return res;
}

template <class T, size_t num_size = 10>
void permate_track_back(std::array<T, num_size> &nums, std::set<T> &track,
                        vector<std::set<T>> &res) {
  if (track.size() == nums.size()) {
    res.push_back(track);
    return;
  }

  for (int i = 0; i < nums.size(); i++) {
    if (track.find(nums[i]) != track.end())
      continue;
    track.insert(nums[i]);
    permate_track_back(nums, track, res);
    track.erase(nums[i]);
  }
}

#endif /* E3415060_4C34_4B8F_9FBC_02C5149656D8 */
