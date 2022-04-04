local function_call
local pb = require "pb"
local protoc = require "protoc"
local serpent = require "serpent"
require "math"

pb.option "enum_as_value"
pb.option "use_default_values"
pb.loadfile "./src/protofile/message_one.pb"

local function print_mth(mth, size)
    for i = 1, size, 1 do
        local row_string = ""
        for j = 1, size, 1 do
            local _tmp = mth[(i-1)*size+j-1];
            row_string = row_string .. "-".._tmp
        end
        print(row_string)
    end
end

local  ECellValue= {
    eFalse = 0,--空的值
    eTrue = 1,--有值
}

local ELineDir = {
    eRow = 0,--行
    eCol = 1,--列
    eLTDiagonal = 2,--左上对角线
    eRTDiagonal = 3,--右上对角线
}
-- Matrix
local function build_mth(size)
    local matrixArray = {}
    for i = 1, size, 1 do
        for j = 1, size, 1 do
            print(math.tointeger(ECellValue.eFalse))
            local flag = math.random(math.tointeger(ECellValue.eFlase),math.tointeger(ECellValue.eTrue))
            print(math.tointeger(ECellValue.eFalse))
            matrixArray[(i-1)*size+j-1] = flag
        end
    end
    print_mth(matrixArray,size)
    -- 生成行的方式
    local cellSelected = {}
    local eLineType = math.random(tonumber(ELineDir.eRow),tonumber(ELineDir.eRTDiagonal))
    -- 生成行
    if eLineType == ELineDir.eRow then
        local rowSelect = math.random(0,size - 1)
        for i = 0, size - 1 do
           local dwIndex = size * rowSelect + i 
           cellSelected[dwIndex] = 1
           matrixArray[dwIndex] = 1
        end
    elseif eLineType == ELineDir.eCol then
        local colSelect = math.random(0,size - 1)
        for i = 0, size - 1 do
           local dwIndex = size * i+ colSelect 
           cellSelected[dwIndex] = 1
           matrixArray[dwIndex] = 1
        end
    elseif eLineType == ELineDir.eLTDiagonal then 
        for i = 0, size - 1 do
           local dwIndex = size * i+ i  
           cellSelected[dwIndex] = 1
           matrixArray[dwIndex] = 1
        end
    elseif eLineType == ELineDir.eRTDiagonal then
        for i = size, 1,-1 do
           local dwIndex = (size - 1) * i  
           cellSelected[dwIndex] = 1
           matrixArray[dwIndex] = 1
        end
    end

    print_mth(matrixArray,size)
end



local function lua_compare_two_table()
    local table1 = {
        ["a"] = 1
    }
    local table3 = {
        ["a"] = 1
    }
    local table2 = table1;
    if table2 == table1 then
        print("same table")
    end
    if table2 == table3 then
        print("same table")
    else
        print("not same table")
    end
end


function lua_function_pass_to_c()
    local new_user = {
        name = "zhangyulan",
        age = 18
    }

    local new_user_data = assert(pb.encode("gl.user", new_user))
    print("after encode" .. new_user_data)
    local afterdecode = assert(pb.decode("gl.user", new_user_data))
    print(afterdecode.name)

    print(serpent.block(afterdecode))
    game.game_parse_pb_to_c("gl.user",new_user_data)
    if lua_compare_two_table then
        lua_compare_two_table()
    else
        print("funtion not found")
    end
    print("...................")
    build_mth(10)
end
-- -- load schema from text (just for demo, use protoc.new() in real world)

-- assert(protoc:load [[
--    message Phone {
--       optional string name        = 1;
--       optional int64  phonenumber = 2;
--    }
--    message Person {
--       optional string name     = 1;
--       optional int32  age      = 2;
--       optional string address  = 3;
--       repeated Phone  contacts = 4;
--    } ]])

-- -- lua table data
-- local data = {
--    name = "ilse",
--    age  = 18,
--    contacts = {
--       { name = "alice", phonenumber = 12312341234 },
--       { name = "bob",   phonenumber = 45645674567 }
--    }
-- }

-- -- encode lua table data into binary format in lua string and return
-- local bytes = assert(pb.encode("Person", data))
-- print(pb.tohex(bytes))

-- -- and decode the binary data back into lua table
-- local data2 = assert(pb.decode("Person", bytes))
-- print(data2.name)

-- local tmp_object = pb.decode "Person"
-- print(tmp_object.name)
-- tmp_object.name="1111"
-- local str_after = pb.encode("Person",tmp_object)
-- print(str_after)
-- print(serpent.block(tmp_object))
-- print(require "serpent".block(data2))
