local dwMaxIndex = 64

function get_flag(qwValue,index)
    local mask = 0x1<<(index - 1)
    print(mask)
    return mask&qwValue
end

print(get_flag(2,2))

local eIndexFlagName
{
    IndexName = 1,
    IndexAge = 2,
    IndexMoney = 3,
}

local fMem = collectgarbage("count")

local array = {}
array[IndexName] = "name"
array[IndexAge] = 15
array[IndexMoney] = 58

local bMem = collectgarbage("count")
print(bMem-fMem)

