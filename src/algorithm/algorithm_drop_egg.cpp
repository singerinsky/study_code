#include "../header.h"

int egg_drop(int dwFloor, int dwEggNum) {
  if (dwFloor == 1)
    return dwEggNum;
  if (dwEggNum == 0)
    return 0;
  int res = dwFloor;
  for (int i = 1; i < dwEggNum + 1; i++) {
    res = min(
        res,
        max(egg_drop(dwFloor, dwEggNum - i), egg_drop(dwFloor - 1, i - 1)) + 1);
  }
  return res;
}

TEST(AlgorithmTest, test_egg_drop) {
  int dwFloor = 10, dwEggNum = 4;
  LOG(INFO) << egg_drop(dwFloor, dwEggNum);
}