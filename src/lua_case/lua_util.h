#ifndef BDBDEA37_82CA_46B3_8870_08100F32E5F4
#define BDBDEA37_82CA_46B3_8870_08100F32E5F4

#include <initializer_list>
#include <type_traits>
#include <utility>

#include "../header.h"
#include "LuaBridge/LuaBridge.h"
#include "LuaBridge/detail/Userdata.h"

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

typedef int LUA_FUNC_HANDLE;

template <typename R> R WarpReturn(lua_State *L) {
  return luabridge::Stack<R>::get(L, -1);
}

template <> inline void WarpReturn<void>(lua_State *L) {}

template <typename R> R call_lua(lua_State *state, const char *function_name) {
  lua_getglobal(state, function_name);
  if (lua_isfunction(state, -1)) {
    lua_pcall(state, 0, 1, 0);
  }
  return WarpReturn<R>(state);
}

template <typename R, typename P1>
R call_lua(lua_State *state, const char *function_name, P1 arg1) {
  lua_getglobal(state, function_name);
  if (lua_isfunction(state, -1)) {
    luabridge::Stack<P1>::push(state, arg1);
    lua_pcall(state, 1, 1, 0);
  }
  return WarpReturn<R>(state);
}

template <typename P1>
float call_lua(lua_State *state, const char *function_name, P1 arg1) {
  lua_getglobal(state, function_name);
  if (lua_isfunction(state, -1)) {
    luabridge::Stack<P1>::push(state, arg1);
    lua_pcall(state, 1, 1, 0);
  }
  return 0.f;
}

template <typename R, typename P1, typename P2>
R call_lua(lua_State *state, const char *function_name, P1 arg1, P2 arg2) {
  lua_getglobal(state, function_name);
  if (lua_isfunction(state, -1)) {
    luabridge::Stack<P1>::push(state, arg1);
    luabridge::Stack<P2>::push(state, arg2);
    lua_pcall(state, 2, 1, 0);
  }
  return WarpReturn<R>(state);
}
// template <typename... ArgPacks>
// void CallLuaFunc(lua_State *state, const char *func_name, ArgPacks... args) {
//   CallLuaFunc(state, func_name, std::forward<ArgPacks...>(args...));
// }
template <typename... ArgPacks>
void CallLuaFunc(lua_State *state, const char *func_name, ArgPacks &&...args) {
  //int rst = lua_getglobal(state, "__G__TRACKBACK__");
  lua_getglobal(state, "__G__TRACKBACK__");
  int err_func = 0;
  if (lua_type(state, -1) != LUA_TFUNCTION) {
    LOG(ERROR) << "init debug functino error!";
    assert(false);
    return;
  } else {
    err_func = lua_gettop(state);
  }

  lua_getglobal(state, func_name);
  if (lua_isfunction(state, -1)) {
    auto _init_list = std::initializer_list<int>{
        // TODO fix value pass
        //(luabridge::Stack<typename std::remove_reference<
        (luabridge::Stack<ArgPacks>::push(state, std::forward<ArgPacks>(args)),
         //    decltype(args)>::type>::push(state,
         //    std::forward<ArgPacks>(args)),
         //>::push(state, std::forward<ArgPacks>(args)),
         0)...};

    auto call_rst = lua_pcall(state, _init_list.size(), 0, err_func);
    if (call_rst) {
      LOG(ERROR) << "function" << func_name << " call error " << call_rst;
      return;
    }
  } else {
    LOG(ERROR) << "call lua function" << func_name << " error";
  }
}

template <typename R, typename... ArgPacks>
R CallLuaFuncWithRet(lua_State *state, const char *func_name,
                     ArgPacks &&...args) {
  assert(func_name);
  lua_getglobal(state, "__G__TRACKBACK__");
  LUA_FUNC_HANDLE err_func = 0;
  if (lua_type(state, -1) != LUA_TFUNCTION) {
    LOG(ERROR) << "init debug function error!";
    lua_pop(state, 1);
    assert(false);
  } else {
    err_func = lua_gettop(state);
  }

  lua_getglobal(state, func_name);
  if (lua_isfunction(state, -1)) {
    auto returnrst = std::initializer_list<int>{
        (luabridge::Stack<ArgPacks>::push(state, std::forward<ArgPacks>(args)),
         0)...};
    int call_rst = lua_pcall(state, sizeof...(args), 1, err_func);
    if (call_rst) {
      LOG(ERROR) << "function" << func_name << " call error " << call_rst<<" type"<<typeid(returnrst).name();
      return WarpReturn<R>(state);
    }
  } else {
    //移除错误栈顶
    lua_pop(state, 1);
    LOG(ERROR) << "call lua function" << func_name
               << " error, function not found!";
    assert(false);
  }
  auto r_ = WarpReturn<R>(state);
  lua_pop(state, 1);
  return r_;
}

lua_State *init_lua_state();

void release_lua_state(lua_State *L);

int function_call_by_lua(lua_State *L);

#define INFO 0
#define ERROR 1
inline void glog_lua(int log_level, const std::string &log_msg) {
  if (log_level == INFO)
    LOG(INFO) << log_msg;
  else if (log_level == ERROR)
    LOG(ERROR) << log_msg;
  else
    LOG(INFO) << log_msg;
}

#endif /* BDBDEA37_82CA_46B3_8870_08100F32E5F4 */
