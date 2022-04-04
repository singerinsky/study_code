#ifndef LUA_TEST_ONE_H
#define LUA_TEST_ONE_H
#include "../header.h"
#include "../util/res_guard.h"
#include "../lua_case/lua_util.h"

TEST(lua_test,test_1)
{
  auto L = init_lua_state();
  int status = 1000;
  lua_getglobal(L,"show_value");
  lua_pushinteger(L,status);
  //lua_pushinteger(L,status);
  if(lua_pcall(L, 1, 1, 0) != 0)
  {
    LOG(INFO)<<"lua call error "<<lua_tostring(L,-1);
  }
  int result;
  result = lua_tointeger(L,-1);
  LOG(INFO)<<"lua result"<<result;
  lua_register(L,"function_call_by_lua",function_call_by_lua);
  lua_settop(L,0);
  lua_getglobal(L, "function_call_by_lua");
  if (lua_pcall(L, 0, 0, 0) != 0)
  {
    LOG(INFO)<<"lua call error "<<lua_tostring(L,-1);
  }
  lua_close(L);
  ASSERT_TRUE(true);
}

TEST(lua_test,test_2)
{
  lua_State* L = init_lua_state();
  //AutoGuard<lua_State> guard(L,&release_lua_state);
  AutoGuard<lua_State> guard(L,[](lua_State* l){
    lua_close(l);
    LOG(INFO)<<"call release function from lamda!";
  });
  lua_pushinteger(L,1000);
  int stack_frame_count = lua_gettop(L);
  LOG(INFO)<<"current stack frame size "<<stack_frame_count;
  int top_value = lua_tointeger(L,-1);
  LOG(INFO)<<"current top frame value:"<<top_value;
  lua_pop(L,1);
  stack_frame_count = lua_gettop(L);
  LOG(INFO)<<"current stack frame size "<<stack_frame_count;
}

TEST(lua_test,test_3)
{
  lua_State* L = init_lua_state();
  //AutoGuard<lua_State> guard(L,&release_lua_state);
  AutoGuard<lua_State> guard(L,[](lua_State* l){
    lua_close(l);
    LOG(INFO)<<"call release function from lamda!";
  });
  int* old = (int*)lua_newuserdata(L,sizeof(int));
  *old = 1111;
  int* point = (int*)lua_touserdata(L,-1);
  LOG(INFO)<<"now memery is "<<*point;
}
#endif // !1