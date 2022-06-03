#include "lua_util.h"
#include "../header.h"
#include "../util/res_guard.h"
#include "LuaBridge/LuaBridge.h"

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

const char *file_name = "lua_functions.lua";
const char *file_name_one = "lua_case.lua";
const std::vector<std::string> all_lua_file = {
    "/home/ubuntu/study_space/src/luafile/protoc.lua",
    "/home/ubuntu/study_space/src/luafile/serpent.lua"
    //    "src/luafile/lua_case.lua"
};

const std::vector<std::string> custom_lua_file = {
    "/home/ubuntu/git_space/study_code/src/luafile/lua_functions.lua",
    "/home/ubuntu/git_space/study_code/src/luafile/lua_define.lua",
    "/home/ubuntu/git_space/study_code/src/luafile/lua_my_debug.lua",
};

void __lua_hook_debug_func_call(lua_State *L, lua_Debug *ar) {
  if (!ar)
    return;
  LOG(INFO) << "hook function call back from"; //<<ar->name<<"  "<<ar->namewhat;
  LOG(INFO) << ar->currentline;
}

void __lua_hook_debug_func_ret(lua_State *L, lua_Debug *ar) {
  if (!ar)
    return;
  // if(ar->namewhat)
  //   LOG(INFO) << "hook function return from" << ar->namewhat;
  // if(ar->source)
  LOG(INFO) << "c function ret " << ar->currentline;
}

lua_State *init_lua_state() {
  LOG(INFO) << "Start";
  lua_State *L = luaL_newstate(); /* create state */
  if (L == NULL) {
    LOG(INFO) << "cannot create state: not enough memory";
    return nullptr;
  }
  luaL_openlibs(L);
  // lua_sethook(L,__lua_hook_debug_func,LUA_MASKCALL,0);
  // init global traceback
  //加载系统使用文件
  for (auto file_str : all_lua_file) {
    int ret = luaL_dofile(L, file_str.c_str());
    if (ret) {
      LOG(INFO) << "load lua file: " << file_str << " failed !"
                << "reason " << ret;
      return nullptr;
    }
  }

  //加载用户自定义文件
  for (auto file_str : custom_lua_file) {
    int ret = luaL_dofile(L, file_str.c_str());
    if (ret) {
      LOG(INFO) << "load lua file: " << file_str << " failed !"
                << "reason " << ret;
      return nullptr;
    }
  }

  // C端可以设置，lua端也可以设置
  // lua_sethook(L,__lua_hook_debug_func_call,LUA_MASKCALL,0);
  // lua_sethook(L,__lua_hook_debug_func_ret,LUA_MASKRET,0);
  luabridge::getGlobalNamespace(L).addFunction("glog", glog_lua);
  static int log_error = 1, log_info = 0;
  return L;
}

void release_lua_state(lua_State *L) {
  lua_close(L);
  LOG(INFO) << "close lua state!";
}

int function_call_by_lua(lua_State *L) {
  LOG(INFO) << "function in c stack......";
  return 1;
}
