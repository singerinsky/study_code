#include "test_coin.h"
#include "../header.h"
#include <limits>

void calc_func_coin(int i, int num, const std::vector<int> &coin_enum,
                    std::vector<int> &result) {
  if (i == 0) {
    result[i] = 0;
    calc_func_coin(i + 1, num, coin_enum, result);
  } else {
    int min = std::numeric_limits<int>::max();
    for (auto coin : coin_enum) {
      if (i >= coin && result[i - coin] + 1 < min) {
        min = result[i - coin] + 1;
      }
    }

    result[i] = min;
    if (i < num)
      calc_func_coin(i + 1, num, coin_enum, result);
  }
}

TEST(AlgorithmTest, test_01) {
  int coin_totoal = 21;
  std::vector<int> coin_enum = {1, 3, 5};
  std::vector<int> result;
  result.resize(coin_totoal + 1);
  calc_func_coin(0, coin_totoal, coin_enum, result);
  int index = 0;
  for (auto r : result) {
    LOG(INFO) << index << ":" << r;
    index++;
  }
}

#define FDIV(dividend, divisor) ((dividend) / ((divisor) != 0 ? (divisor) : 1))
#define DAY_SECONDS 60 * 60 * 24

uint32_t getDiffDays(time_t smallTime_, time_t bigTime_, uint32_t benchmark_) {
  uint32_t diffDays = 0;
  int m_nTimeZone = 8 * 3600;
  if (smallTime_ >= bigTime_ || benchmark_ >= DAY_SECONDS) {
    return diffDays;
  }
  smallTime_ += m_nTimeZone;
  bigTime_ += m_nTimeZone;

  smallTime_ -= benchmark_;
  bigTime_ -= benchmark_;
  LOG(INFO) << "big day" << FDIV(bigTime_, DAY_SECONDS) << " smail day"
            << FDIV(smallTime_, DAY_SECONDS);
  diffDays = FDIV(bigTime_, DAY_SECONDS) - FDIV(smallTime_, DAY_SECONDS);
  return diffDays;
}

TEST(AlgorithmTest, test_03) {
  int day_one =
      getDiffDays(1645909200, 1645909200 + DAY_SECONDS - 18001, 18000);
  int day_two = getDiffDays(1645909200, 1646495999, 18000);
  int day_3 = getDiffDays(1645909200, 1646495999 + 18000 + 1, 18000);
  LOG(INFO) << "day_one: " << day_one << " day_two: " << day_two
            << "day 3: " << day_3;
}