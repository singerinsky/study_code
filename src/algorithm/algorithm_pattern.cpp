#include "../header.h"

bool do_pattern(const std::string &s, int i, const std::string p, int j) {
  int m = s.size();
  int n = p.size();
  if (j == n) {
    return i == m;
  }
  //如果被匹配字符串已经到了末尾
  if (i == m) {
    //检查p后续的字符串是否能匹配空串
    //如果是单数的，必然不能匹配空串，因为只有.*或者任意字符*才能匹配空串
    if ((n - 1) % 2 == 1) {
      return false;
    }
    for (; j + 1 < n; j += 2) {
      //第二个字母不是*,失败
      if (p[j + 1] != '*') {
        return false;
      }
    }
    return true;
  }

  bool res = false;
  //如果遇到通配符
  if (s[i] == p[j] || p[j] == '.') {
    //如果后面一位是*,判断0次匹配和多少次匹配是否能满足
    if (j < n - 1 && p[j + 1] == '*') {
      res = do_pattern(s, i, p, j + 2) || do_pattern(s, i + 1, p, j);
    } else {
      //匹配了一次，继续前进
      res = do_pattern(s, i + 1, p, j + 1);
    }
  } else {
    //没有匹配到，看看是否能通过0次匹配往后走
    if (j < n - 1 && p[j + 1] == '*') {
      res = do_pattern(s, i, p, j + 2);
    } else {
      res = false;
    }
  }
  return res;
}

TEST(Algorithm, test_pattern) {
  std::string s = "name";
  std::string p = "n.*1";
  LOG(INFO) << do_pattern(s, 0, p, 0);
}