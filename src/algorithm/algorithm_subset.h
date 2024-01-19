#ifndef E3415060_4C34_4B8F_9FBC_02C5149656D8
#define E3415060_4C34_4B8F_9FBC_02C5149656D8
#include "../header.h"

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
#endif /* E3415060_4C34_4B8F_9FBC_02C5149656D8 */
