#include "../header.h"
#include <algorithm>

// 因为lambda使用了值捕获外部变量，那他会创建自己的副本，那就回报错
int MinDistanceWithLambda(const char *str1, const char *str2) {
  std::function<int(int, int)> dp_func;
  // 要正确运行，只能用引用捕获
  // dp_func = [&](int index_1, int index_2) -> int {
  dp_func = [=](int index_1, int index_2) -> int {
    LOG(INFO) << index_1 << ":" << index_2;
    if (index_1 == -1)
      return index_2 + 1;
    if (index_2 == -1)
      return index_1 + 1;
    if (str1[index_1] == str2[index_2]) {
      LOG(INFO) << str1[index_1];
      return dp_func(index_1 - 1, index_2 - 1);
    } else {
      int value1 =
          dp_func(index_1, index_2 - 1) + 1; //删除一个str1的字符，检查是否匹配
      int value2 =
          dp_func(index_1 - 1, index_2) + 1; //插入一个str1的字符，检查是否匹配
      int value3 =
          dp_func(index_1 - 1, index_2 - 1) + 1; //选择一个str2的字符到str1
      return std::min(value1, std::min(value2, value3));
    }
  };
  LOG(INFO) << "start call!";
  return dp_func(strlen(str1) - 1, strlen(str2) - 1);
}

TEST(Algorithm, test_min_dis) {
  LOG(INFO) << MinDistanceWithLambda("name", "na");
}

int db_function(const char *str1, int index_1, const char *str2, int index_2) {
  LOG(INFO) << index_1 << ":" << index_2;
  if (index_1 == -1)
    return index_2 + 1;
  if (index_2 == -1)
    return index_1 + 1;
  if (str1[index_1] == str2[index_2]) {
    LOG(INFO) << str1[index_1];
    return db_function(str1, index_1 - 1, str2, index_2 - 1);
  } else
    return std::min({db_function(str1, index_1, str2, index_2 - 1) + 1,
                     db_function(str1, index_1 - 1, str2, index_2) + 1,
                     db_function(str1, index_1 - 1, str2, index_2 - 1) + 1});
}

int MinDistanceWithOutLambda(const char *str1, const char *str2) {

  LOG(INFO) << "start call!";
  return db_function(str1, strlen(str1) - 1, str2, strlen(str2) - 1);
}

TEST(Algorithm, test_min_dis_without_lam) {
  LOG(INFO) << MinDistanceWithOutLambda("name", "na");
}
