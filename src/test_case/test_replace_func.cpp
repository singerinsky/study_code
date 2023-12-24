#include "../header.h"

#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

void original_function() { printf("Hello, world!\n"); }

void replacement_function() {
  printf("Replacement function calle...........\n");
}

void enable_write(void *addr, size_t len) {
  long pagesize = sysconf(_SC_PAGESIZE);
  long pagestart = (long)addr & ~(pagesize - 1);
  int rst = mprotect((void *)pagestart, pagesize * 2,
                     PROT_READ | PROT_WRITE | PROT_EXEC);
  LOG(INFO) << "do mprotect rst:" << rst;
}

void disbale_write(void *addr, size_t len) {
  long pagesize = sysconf(_SC_PAGESIZE);
  long pagestart = (long)addr & ~(pagesize - 1);
  if (mprotect((void *)pagestart, pagesize * 2, PROT_READ) == -1) {
    perror("mprotect");
  }
}

void replace_function(void *target_function, void *replacement_function) {
  unsigned long long addr = (unsigned long long)replacement_function;
  unsigned char buf[12] = {0x48, 0xb8, 0, 0, 0, 0, 0, 0, 0, 0, 0xff, 0xe0};
  for (int i = 0; i < 8 && (i + 2) < (int)sizeof(buf); i++) {
    buf[i + 2] = addr & 0xff;
    addr >>= 8;
  }
  addr = (unsigned long long)target_function;
  enable_write(target_function, sizeof(void *));
  //*(target_function) = replacement_function;
  memcpy(target_function, buf, sizeof(buf));
  // disbale_write(target_function, 0);
  //  enable_write(target_function, sizeof(void *));
  LOG(INFO) << "after memcpy";
}

TEST(TestReplace, test001) {
  auto ofunction_ptr = (void *)original_function;
  auto rfunction_ptr = (void *)replacement_function;
  // 调用原始函数
  original_function();

  // 将函数指针指向替换函数
  replace_function(ofunction_ptr, rfunction_ptr);
  LOG(INFO) << "Before...";
  original_function();
  LOG(INFO) << "END OF MAIN";
  // 调用替换函数
  // ofunction_ptr();
}