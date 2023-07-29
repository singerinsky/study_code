#ifndef B53FA443_C94C_40CF_8EE6_B4AF469FF9CC
#define B53FA443_C94C_40CF_8EE6_B4AF469FF9CC
#include "../header.h"
#define StFdCleanup(fd)                                                        \
  impl__StFdCleanup _ST_free_##fd(                                             \
      &fd) // 定义一个宏，用于创建 impl__StFdCleanup 对象并传入指向 fd 的引用

#define StStfdCleanup(stfd)                                                    \
  impl__StFdCleanup _ST_free_##stfd(                                           \
      NULL, &stfd) // 定义一个宏，用于创建 impl__StFdCleanup 对象并传入指向 stfd
                   // 的引用

class impl__StFdCleanup {
  int *fd_;

public:
  impl__StFdCleanup(int *fd) : fd_(fd) {} // 构造函数，接收一个指向 fd 的引用
  virtual ~impl__StFdCleanup() {} // 虚析构函数，用于基类的多态销毁
};

TEST(TestMarco, test001) {
  int fd = 0;
  StFdCleanup(fd); // 创建一个 impl__StFdCleanup 对象，并传入指向 fd 的引用
}

#endif /* B53FA443_C94C_40CF_8EE6_B4AF469FF9CC */
