#include "algorithm_kuohao.h"
#include "../header.h"

vector<string> generate_kuohao(int n) {
  if (n == 0)
    return {};
  //记录所有合法的括号组合
  vector<string> res;
  // 回溯过程中的路径
  string cur;
  //可用的左括号和右括号数量为n
  kuohao_backtrack(res, cur, n, n);
  return res;
}

void kuohao_backtrack(vector<string> &res, string &cur, int left, int right) {
  //小于0，肯定不对
  if (left < 0 || right < 0)
    return;
  //左边的括号剩下的多，不合法
  if (left > right)
    return;

  //左右括号都不剩余了，记录结果
  if (left == 0 && right == 0) {
    res.push_back(cur);
    return;
  }

  // 尝试放一个左括号
  cur.push_back('(');
  kuohao_backtrack(res, cur, left - 1, right);
  cur.pop_back();

  // 尝试放一个右括号
  cur.push_back(')');
  kuohao_backtrack(res, cur, left, right - 1);
  cur.pop_back();
}

// 测试 generate_kuohao 函数
TEST(AlgorithmTest, TestBK001) {
  vector<string> expected = {"((()))", "(()())", "(())()", "()(())", "()()()"};
  vector<string> result = generate_kuohao(3);
  EXPECT_EQ(result, expected);
}

// 测试 generate_kuohao 函数边界情况
TEST(AlgorithmTest, TestBK002) {
  vector<string> expected = {};
  vector<string> result = generate_kuohao(0);
  EXPECT_EQ(result, expected);
}
