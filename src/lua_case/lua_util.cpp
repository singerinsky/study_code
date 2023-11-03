#include "lua_util.h"
#include "../header.h"
#include "../util/res_guard.h"
#include "LuaBridge/LuaBridge.h"
#include <iostream>
#include <unistd.h>

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

const char *file_name = "lua_functions.lua";
const char *file_name_one = "lua_case.lua";
const std::vector<std::string> all_lua_file = {
    "/../src/luafile/protoc.lua", "/../src/luafile/serpent.lua"
    //    "src/luafile/lua_case.lua"
};

const std::vector<std::string> custom_lua_file = {
    "/../src/luafile/lua_functions.lua",
    "/../src/luafile/lua_define.lua",
    "/../src/luafile/lua_my_debug.lua",
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
int GetCurrentDIR(char *dirBuff, uint32 uSize) {

  if (getcwd(dirBuff, uSize) != NULL) {
    std::cout << "Current working directory: " << dirBuff << std::endl;
    return -1;
  } else {
    std::cerr << "Failed to get current working directory" << std::endl;
    return 1;
  }
}

void get_lua_path(lua_State *L) {
  lua_getglobal(L, "package");
  lua_getfield(L, -1, "path");
  const char *packagePath = lua_tostring(L, -1);
  LOG(INFO) << " current lua path:" << packagePath;
  lua_settop(L, 0);
}

void set_lua_path(lua_State *L, std::string strCustomPath) {
  // 获取 package.path 的值
  lua_getglobal(L, "package");
  lua_getfield(L, -1, "path");
  const char *packagePath = lua_tostring(L, -1);

  // 添加新的模块搜索路径
  // std::string newPackagePath = packagePath + ";/your/module/directory/?.lua";
  std::string newPackagePath = packagePath;
  newPackagePath.append(";");
  newPackagePath.append(strCustomPath);
  newPackagePath.append("/?.lua");

  // 设置新的 package.path
  lua_pushstring(L, newPackagePath.c_str());
  lua_setfield(L, -3, "path");

  // 清理栈空间
  lua_pop(L, 2);

  // 在这里执行你的 Lua 代码

  // lua_close(L);
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
  get_lua_path(L);
  char buffDir[512];
  GetCurrentDIR(buffDir, 512);
  std::string strLuaFindPath;
  strLuaFindPath.append(buffDir);
  strLuaFindPath.append("/../src/luafile");
  set_lua_path(L, strLuaFindPath);

  get_lua_path(L);
  LOG(INFO) << buffDir;
  for (auto file_str : all_lua_file) {
    std::string strFilePath = buffDir;
    LOG(INFO) << "word dir: " << strFilePath;
    strFilePath.append(file_str);
    int ret = luaL_dofile(L, strFilePath.c_str());
    if (ret) {
      LOG(INFO) << "load lua file: " << strFilePath << " failed !"
                << "reason " << ret;
      return nullptr;
    }
  }

  //加载用户自定义文件

  for (auto file_str : custom_lua_file) {
    std::string strFilePath = buffDir;
    LOG(INFO) << "word dir: " << strFilePath;
    strFilePath.append(file_str);
    int ret = luaL_dofile(L, strFilePath.c_str());
    if (ret) {
      LOG(INFO) << "load lua file: " << strFilePath << " failed !"
                << "reason " << ret;
      return nullptr;
    }
  }

  // C端可以设置，lua端也可以设置
  // lua_sethook(L,__lua_hook_debug_func_call,LUA_MASKCALL,0);
  // lua_sethook(L,__lua_hook_debug_func_ret,LUA_MASKRET,0);
  luabridge::getGlobalNamespace(L).addFunction("glog", glog_lua);
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
