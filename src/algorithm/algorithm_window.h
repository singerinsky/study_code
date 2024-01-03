#ifndef C0FB3424_1C49_426B_A5CD_3F773628ADEB
#define C0FB3424_1C49_426B_A5CD_3F773628ADEB
#include "../header.h"
#include <climits>

//通过最小的滑动窗口，获取包含target字符串中所有字符的最短字符串
inline std::string SearchMinWindow(const std::string &source,
                                   const std::string &target) {
  std::map<char, int> need, window;
  //先统计所有需要的字符的数量
  for (char c : target) {
    need[c]++;
  }

  //窗口边界
  int left = 0, right = 0;
  //满足的字符数量
  int valid = 0;
  int start = 0, len = INT_MAX;
  while (right < source.size()) {
    char c = source[right];
    right++;
    //如果是我们需要的字符
    if (need.count(c)) {
      //更新窗口中获取的数据
      window[c]++;
      if (window[c] == need[c])
        //更新整个满足的数量
        valid++;
    }

    //条件已经满足，缩小窗口
    while (valid == need.size()) {
      //如果两者的差小于当前最小值，就更新子字符串的起始位置
      if (right - left < len) {
        start = left;
        len = right - left;
      }
      //现在开始收缩
      char d = source[left];
      left++;
      //如果把需要的字符串收缩掉了，那么要调整
      if (need.count(d)) {
        if (window[d] == need[d]) {
          valid--;
        }
        window[d]--;
      }
    }
  }
  return len == INT_MAX ? "" : source.substr(start, len);
}

//变种1.判断S中是否存在一个子串是T的一种全排列
inline bool CheckInclusion(const std::string &target,
                           const std::string &source) {
  std::map<char, int> need, window;
  int left = 0, right = 0;
  int valid = 0;
  for (auto c : target) {
    need[c]++;
  }

  while (right < source.size()) {
    char c = source[right];
    //右边移动
    right++;
    if (need.count(c)) {
      window[c]++;
      //如果需要的字符数量够了
      if (window[c] == need[c])
        valid++;
    }

    //判断收缩条件是，窗口大小，大于等于匹配字符串长度
    if (right - left == target.size()) {
      //如果字符凑够了，就返回true
      if (valid == need.size())
        return true;
      //如果不够的话，就要收缩
      char d = source[left];
      left++;
      //如果是需要的字符
      if (need.count(d)) {
        //如果数量刚刚好
        if (window[d] == need[d])
          valid--;
        //减少滑动窗口的数量
        window[d]--;
      }
    }
  }
  return false;
}

#endif /* C0FB3424_1C49_426B_A5CD_3F773628ADEB */
