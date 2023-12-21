#include "algorithm_window.h"

TEST(Algorithm, test001) {
  std::string source = "ABCBOCBDBDSBD";
  std::string need = "CBC";
  std::string strResult = SearchMinWindow(source, need);
  LOG(INFO) << strResult;
}

TEST(Algorithm, test002) {
  std::string source = "ABCBOCBDBDSBD";
  std::string need = "COB";
  auto rst = CheckInclusion(need, source);
  LOG(INFO) << "find result:" << rst;
}