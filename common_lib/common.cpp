#include <unistd.h>
extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

static int my_add(lua_State* L)
{
    ::sleep(20);
    int i = 100;
    int j = 99;
    lua_pushnumber(L, i - j);
    return i - j;
}

int luaopen_libluatestlib(lua_State* L)
{
    luaL_Reg luaLoadFun[] = { { "my_add", my_add }, { NULL, NULL } };
    luaL_newlib(L, luaLoadFun);
    return 1;
}
}
