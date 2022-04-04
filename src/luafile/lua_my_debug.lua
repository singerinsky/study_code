require "serpent"
require "debug"

function function_call_test_upvalue(value)
    print("call function call test up value " .. value)
    glog(LOG_LEVEL_ERR, "log from lua")
    glog(LOG_LEVEL_INFO, "log from lua")
    OUTPUT_LOG("hao ba", 1, 2, 33, 3)
end
