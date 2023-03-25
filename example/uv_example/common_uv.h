#ifndef A192BE15_CFE8_41AC_B079_B2E7DE201F50
#define A192BE15_CFE8_41AC_B079_B2E7DE201F50
#include "uv.h"

void common_close_cb(uv_handle_t *handle);

#define SINGLETON_FUN_DEF(classname)                                           \
public:                                                                        \
  static classname *GetInstance();                                             \
                                                                               \
protected:                                                                     \
  classname();                                                                 \
  ~classname();                                                                \
  classname(const classname &) = delete;                                       \
  classname(classname &&) = delete;                                            \
  classname &operator=(const classname &) = delete;                            \
  classname &operator=(classname &&) = delete;

#define SINGLETON_FUN_BODY(classname)                                          \
  classname *classname::GetInstance() {                                        \
    static std::once_flag _flag;                                               \
    static classname _instance;                                                \
    std::call_once(_flag, [&]() { (_instance).Init(); });                      \
    return &_instance;                                                         \
  }

#endif /* A192BE15_CFE8_41AC_B079_B2E7DE201F50 */
