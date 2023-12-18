weakTable = {}
weakTable[1] = function() print("i am the first element") end
weakTable[2] = function() print("i am the second element") end
weakTable[3] = {10, 20, 30}

setmetatable(weakTable, {__mode = "v"})        -- 设置为弱表

print(#(weakTable))            -- 3

ele = weakTable[1]        -- 给第一个元素增加一个引用
collectgarbage()
print(#(weakTable))         -- 1，第一个函数引用为1，不能gc

ele = nil                -- 释放引用
collectgarbage()
print(#(weakTable))            -- 0，没有其他引用了，全部gc