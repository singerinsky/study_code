#include "../header.h"

int calc_coin_plan(std::vector<int> vecCoinType, size_t dwAmount) {
  if (dwAmount == 0)
    return 1;

  size_t dwCoinNumber = vecCoinType.size();
  std::vector<std::vector<int>> dp(dwCoinNumber + 1,
                                   std::vector<int>(dwAmount + 1));

  for (size_t start = 0; start <= vecCoinType.size(); start++) {
    dp[start][0] = 1;
  }

  for (int i = 1; i <= dwCoinNumber; i++)
    for (int j = 1; j <= dwAmount; j++) {
      if (j - vecCoinType[i - 1] >= 0) {
        dp[i][j] = dp[i - 1][j] + dp[i][j - vecCoinType[i - 1]];
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  return dp[dwCoinNumber][dwAmount];
}

TEST(AlgorithmTest, CoinSelect) {
  std::vector<int> vec = {1, 2, 4, 5};
  LOG(INFO) << calc_coin_plan(vec, 3);
}