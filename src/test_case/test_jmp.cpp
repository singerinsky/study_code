#include "../header.h"
#include <setjmp.h>
static jmp_buf env_jmp;
void execute_function() {
  LOG(INFO) << "call start!";
  longjmp(env_jmp, 1);
  LOG(INFO) << "call end!";
}

void test_jmp() {
  int i = 0;
  int rst = setjmp(env_jmp);
  if (rst == 0) {
    i++;
    execute_function();
    LOG(INFO) << "call end!";
  } else {
    LOG(INFO) << "jmp end!" << i;
  }
  LOG(INFO) << "start jmp";
}

TEST(BaseTest, test_jmp) { test_jmp(); }