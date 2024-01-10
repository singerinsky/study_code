#include "algorithm_lru.h"
#include <glog/logging.h>
#include <gtest/gtest.h>
// LRUCache 类的单元测试
class LRUCacheTest : public testing::Test {
protected:
  void SetUp() override { cache = new LRUCache<int, int>(2); }

  void TearDown() override { delete cache; }

  LRUCache<int, int> *cache;
};

// 测试 MakeRecently() 方法
TEST_F(LRUCacheTest, MakeRecentlyTest) {
  cache->Put(1, 1);
  cache->Put(2, 2);
  cache->MakeRecently(2);
  EXPECT_EQ(*(cache->Get(2)), 2);
  LOG(INFO) << "finish test";
}

// 测试 AddRecently() 方法
TEST_F(LRUCacheTest, AddRecentlyTest) {
  cache->AddRecently(1, 1);
  EXPECT_EQ(*(cache->Get(1)), 1);
}