#ifndef F8C402F2_34F1_48E7_A899_C69C121569D6
#define F8C402F2_34F1_48E7_A899_C69C121569D6

#include "../header.h"
#include <atomic>
#include <future>
#include <gtest/gtest.h>
#include <setjmp.h>

jmp_buf env;

void foo() {
  int ret = setjmp(env);
  if (ret == 0) {
    // 正常流程
    LOG(INFO) << "normal !";
  } else {
    // 长跳转发生后的处理
    LOG(INFO) << "after long jump !";
  }
}

void bar() {
  longjmp(env, 1); // 长跳转到foo函数中的longjmp处
}

TEST(TestCorutine, test001) {

  foo();
  bar();
}

#endif /* F8C402F2_34F1_48E7_A899_C69C121569D6 */
