#include "lua_pure.h"
#include "../header.h"
#include "lua_util.h"

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

TEST(LuaTest, test_lua_hook) { test_lua_hook(); }
TEST(LuaTest, test_01) { test_01(); }
