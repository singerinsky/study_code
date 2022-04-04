#ifndef F6155747_3F37_4641_8981_9A89E1A7FD70
#define F6155747_3F37_4641_8981_9A89E1A7FD70
#include "../header.h"
#include "../util/class_sample.h"
#include "LuaBridge/LuaBridge.h"
#include "gtest/gtest.h"
#include "../util/res_guard.h"
#include "../lua_case/lua_util.h"
using namespace luabridge;
TEST(lua_bridge,test_01)
{
lua_State* L = init_lua_state();
  //AutoGuard<lua_State> guard(L,&release_lua_state);
  AutoGuard<lua_State> guard(L,[](lua_State* l){
    lua_close(l);
    LOG(INFO)<<"call release function from lamda!";
  });
    luabridge::getGlobalNamespace(L)
    .beginClass<SampleClass>("SampleClass")
    .addConstructor<void(*)(void)>()
    .addFunction("getid",&SampleClass::GetId)
    .addFunction("setid",&SampleClass::SetId)
    .endClass();

    luabridge::getGlobalNamespace(L)
    .beginClass<SampleClassManager>("SampleClassManager")
    .addStaticFunction("GetInstance",&SampleClassManager::GetInstance)
    .addFunction("GetObject",&SampleClassManager::GetObject)
    .addFunction("AddSampleObject",&SampleClassManager::AddSampleObject)
    .addFunction("Dump",&SampleClassManager::Dump)
    .endClass();

  SampleClassManager::GetInstance()->AddSampleObject(100,new SampleClass);
  lua_getglobal(L,"test_lua_bridge");
  lua_pcall(L,0,0,0);
  
  lua_getglobal(L,"test_static_instance");
  lua_pcall(L,0,0,0);
}

TEST(lua_bridge,test_02)
{
lua_State* L = init_lua_state();
  //AutoGuard<lua_State> guard(L,&release_lua_state);
  AutoGuard<lua_State> guard(L,[](lua_State* l){
    lua_close(l);
    LOG(INFO)<<"call release function from lamda!";
  });
    luabridge::getGlobalNamespace(L)
    .beginClass<SampleClass>("SampleClass")
    .addConstructor<void(*)(void)>()
    .addFunction("getid",&SampleClass::GetId)
    .addFunction("setid",&SampleClass::SetId)
    .endClass();

    luabridge::getGlobalNamespace(L)
    .beginClass<SampleClassManager>("SampleClassManager")
    .addStaticFunction("GetInstance",&SampleClassManager::GetInstance)
    .addFunction("GetObject",&SampleClassManager::GetObject)
    .addFunction("AddSampleObject",&SampleClassManager::AddSampleObject)
    .addFunction("Dump",&SampleClassManager::Dump)
    .endClass();

  LOG(INFO)<<"call 1";
  call_lua(L,"show_value",999);
  LOG(INFO)<<"call 2";
  LOG(INFO)<<call_lua<int,int>(L,"show_value_with_param",999);
  LOG(INFO)<<"call 3";
  LOG(INFO)<<call_lua<float,int>(L,"show_value_with_param",999);
  LOG(INFO)<<"call 4";
  call_lua<void,int>(L,"show_value_with_param",999);
  LOG(INFO)<<"call 5";
  call_lua<void,float>(L,"show_value_with_param",999);


  SampleClass* object = new SampleClass;
  object->SetId(999999);
  LuaRef process_func = getGlobal(L,"call_function_with_object");
  if(process_func.isFunction())
  {
      auto rst = process_func(object);
      LOG(INFO)<<"function call function with object return "<<rst;
  }
  LuaRef ref = getGlobal(L,"g_value_test");
  if(ref.isNumber())
  {
    LOG(INFO)<<ref;
  }
  LuaRef ref_integer = getGlobal(L, "g_value_integer");
  if(ref_integer.isNumber())
  {
    LOG(INFO)<<ref_integer.tostring();
    int64 number = ref_integer.cast<int64>();
  }
}

#endif /* F6155747_3F37_4641_8981_9A89E1A7FD70 */
