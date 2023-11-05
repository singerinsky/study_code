#include "lua_pure.h"
#include "../header.h"
#include "lua.h"
#include "lua_util.h"
#include <unistd.h>

void test_lua_hook() {

  lua_State *L = init_lua_state();
  AutoGuard<lua_State> guard(L, [](lua_State *l) {
    lua_close(l);
    LOG(INFO) << "call release function from lamda!";
  });

  LOG(INFO) << "begin lua pure test~!";
  int status = 1000;
  std::string name = "guanlei";
  float fvalue = 0.1f;
  auto ret =
      CallLuaFuncWithRet<int>(L, "show_value_with_param", status, name, fvalue);
  LOG(INFO) << "return is ....." << ret;
}

void test_01() {
  lua_State *L = init_lua_state();
  AutoGuard<lua_State> guard(L, [](lua_State *l) {
    lua_close(l);
    LOG(INFO) << "call release function from lamda!";
  });
  CallLuaFunc(L, "function_call_test_upvalue", 1);
}

void test_mem() {
  lua_State *L = init_lua_state();

  if (L == nullptr) {
    LOG(ERROR) << " lua state is null!";
    return;
  }

  // lua_setglobal(L, 0);
  lua_getglobal(L, "DumpLuaMem");
  if (lua_isfunction(L, -1)) {
    lua_pcall(L, 0, 0, 0);
  }

  for (int i = 1; i < 100; i++) {
    usleep(100000);
    for (int j = 1; j < 100; j++) {
      LOG(INFO) << "push int size:" << 100 * i + j;
      lua_pushinteger(L, 100);
    }

    // lua_getglobal(L, "DumpLuaMem");
    // if (lua_isfunction(L, -1)) {
    //   lua_pcall(L, 0, 0, 0);
    // }
    // lua_setglobal(L, 0);
  }
}

TEST(LuaTest, test_lua_hook) { test_lua_hook(); }
TEST(LuaTest, test_01) { test_01(); }
TEST(LuaTest, test_mem) { test_mem(); }