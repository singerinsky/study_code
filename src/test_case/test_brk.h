#ifndef D6168AA7_DC2C_4A39_9E61_6A87DB57EC44
#define D6168AA7_DC2C_4A39_9E61_6A87DB57EC44

#include "../header.h"

void function_brk_test() {

  size_t MAX_BYTES = 64 * 1024; // ThreadCache 申请的最大内存
  size_t NLISTS = 184; //数组元素总的有多少个，由对齐规则计算得来
  size_t PAGE_SHIFT = 12;
  size_t NPAGES = 129;

  void *ptr = sbrk(0);
  void *newptr = sbrk((NPAGES - 1) * (1 << PAGE_SHIFT));
  LOG(INFO) << (1 << PAGE_SHIFT);
  LOG(INFO) << "page id " << ((long long)newptr >> PAGE_SHIFT);
  void *after = sbrk(0);
  LOG(INFO) << (char *)after - (char *)newptr;
}

TEST(TestMemery, brk) {
  function_brk_test();
  function_brk_test();
}

#endif /* D6168AA7_DC2C_4A39_9E61_6A87DB57EC44 */
