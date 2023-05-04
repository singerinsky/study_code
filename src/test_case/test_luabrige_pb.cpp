#include "test_luabrige_pb.h"
#include "../util/class_sample.h"
#include "LuaBridge/LuaBridge.h"
#include "gtest/gtest.h"
#include "../util/res_guard.h"
#include "../lua_case/lua_util.h"
#include "message.pb.h"
#include <benchmark/benchmark.h>
using namespace luabridge;

void game_parse_pb_to_c(const std::string& message_name,const std::string& message_content )
{
  gl::CSRequireUserInfo user_from_lua;
  user_from_lua.ParseFromString(message_content);
  LOG(INFO) << "call from lua";
  LOG(INFO) << user_from_lua.name();
}

void test_tran_pb_to_lua()
{
  lua_State *L = init_lua_state();
  if(!L)
  {
    return;
  }
  //AutoGuard<lua_State> guard(L,&release_lua_state);
  AutoGuard<lua_State> guard(L,[](lua_State* l){
    lua_close(l);
    LOG(INFO)<<"call release function from lamda!";
  });
    luabridge::getGlobalNamespace(L)
    .beginNamespace("game")
    .addFunction("game_parse_pb_to_c", &game_parse_pb_to_c);
   
  lua_getglobal(L,"lua_function_pass_to_c");
  lua_pcall(L,0,0,0);
}

TEST(LuaTest, pb_1) { test_tran_pb_to_lua(); }