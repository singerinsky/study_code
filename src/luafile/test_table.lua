require "math"
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

--local test_table = {1,2,34,4,5}
local test_table = {}
test_table["name"] = "guanlei"
test_table["name1"] = "guanlei1"
table.insert(test_table,100)

for key,value in pairs(test_table) do
	print(key..":"..value)
end
print(".........")
print(#test_table)
print(type(test_table))
print("............................................")
local sub_table = {1,2,34,4,5}
local table_1 = {}
table.insert(table_1,sub_table)
table.insert(table_1,"guanlei1")
table.insert(table_1,"guanlei2")
table_1["shit"] = "shit"

local function build_split(dep)
    local string = ""
    for i = 1, dep , 1 do
       string = string.."----" 
    end
    return string
end

local function _dump_table(table_to_dump,dep)
    dep = dep + 1
    if(type(table_to_dump) ~= "table") then
        print(build_split(dep).."value:"..table_to_dump)
        return
    end
    for key, value in pairs(table_to_dump) do
       print(build_split(dep).."key:"..key) 
       _dump_table(value,dep)
    end
end


local function dump_table(table_to_dump)
    local dep = 0
   _dump_table(table_to_dump,0) 
end

print("table size "..#table_1)
dump_table(table_1)


