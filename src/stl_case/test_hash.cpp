#include "../header.h"

unsigned int bkdr_hash(const std::string &str) {
  const unsigned int seed = 131; // 31 131 1313 13131 131313
  unsigned int hash = 0;
  for (char ch : str) {
    hash = hash * seed + ch;
  }
  return hash;
}

TEST(TestHash, test001) {
  std::string name1 = "guanlei";
  std::string name2 = "guanleie";
  LOG(INFO) << "guanlei hash:" << bkdr_hash(name1);
  LOG(INFO) << "guanlei hash:" << bkdr_hash(name1);
  LOG(INFO) << "guanlei hash:" << bkdr_hash(name2);
  if (bkdr_hash(name1) == bkdr_hash(name2)) {
    LOG(INFO) << "equal";
  }
}