#include "lib_header.h"
#include "gtest/gtest.h"
#include <glog/logging.h>

template <class T> void test_split_define(T *t) {}

template <class T> void test_split_define(const T &t) {
  LOG(INFO) << "do execute";
}
template <> void test_split_define(const std::string &t) {
  LOG(INFO) << "do execute";
}

template <> void test_split_define(const int &t) { LOG(INFO) << "do execute"; }

void test_reachable() { LOG(INFO) << "do execute test_reachable"; }