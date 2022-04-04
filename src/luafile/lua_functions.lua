package.path = package.path .. ";src/luafile/?.lua;src/protofile/message_one.pb"

function func_for_hook_test()
    print("function for hook test")
end

function show_value(value)
    print("......................", value)
    func_for_hook_test()
end

function show_value_with_param(value)
    print("......................", value)
    return value + 1
end

function increament(value)
    value = value + 1
end

function show_value_with_param(value1, value2, value3)
    print("......................" .. value1 .. ":" .. value2 .. ":" .. value3)
    local count = MakeCounter()
    print(count())
    print(count())
    print(count())
    print(count())
    print(count())
    local index = 1
    increament(index)
    increament(index)
    increament(index)
    increament(index)
    increament(index)
    increament(index)
    print(index .. "........")
    return "10001";
end

function MakeCounter()
    local t = 0
    return function()
        t = t + 1
        return t
    end
end

function call_c_function()
    print("uuuuuuuuuuuuuuuuuu")
end

function test_lua_bridge()
    local new_sampleclass = SampleClass()
    new_sampleclass:setid(1000)
    print(new_sampleclass:getid())
    local object_manager = SampleClassManager:GetInstance()
    -- 这样的话会有野指针，已经加入manager管理的对象是由lua调用注册的construct 生成，那它的生命周期是lua控制的，就会被gc
    object_manager:AddSampleObject(2, new_sampleclass)
end

function test_static_instance()
    local object_manager = SampleClassManager:GetInstance()
    object_manager:Dump()
end

function call_function_with_object(object)
    print(object:getid())
    return "hello world"
end

g_value_test = 111111
g_value_integer = 11111111111111

