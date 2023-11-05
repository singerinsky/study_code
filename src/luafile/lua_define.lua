require "serpent"
require "debug"

LOG_LEVEL_INFO = 0
LOG_LEVEL_ERR = 1
function OUTPUT_LOG(...)
    local file_name = debug.getinfo(2).source
    local line = debug.getinfo(2).currentline
    local s = ""
    for i, v in pairs {...} do
        s = tostring(v) .. s
    end
    glog(LOG_LEVEL_INFO, file_name .. ":" .. line .. "  " .. s)
end

function __debug_info(event, line)
    print("event " .. event .. " in line ")
    -- print(debug.traceback())
end

function __G__TRACKBACK__(msg)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(msg) .. "\n")
    print(debug.traceback())
    print("----------------------------------------")
end

function DumpLuaMem()
    print(collectgarbage("count"))--打印当前的内存使用情况
end
print("init define....!")

-- debug.sethook(__debug_info,"c")
