local EConfig = {
    ERowCount = 20,
    EColumnCount = 20,
}
--[[-example
local g_veczone_back = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
}
-]]--
local g_veczone = {}
for cindex=1,EConfig.ERowCount do 
    g_veczone[cindex] = {}
    for rindex=1,EConfig.ERowCount do 
        g_veczone[cindex][rindex] = 1
    end
end

function print_zone(vecZone)
    local row_count = #vecZone[1]
    local row_index = 1
    for _,value in pairs(vecZone) do
        local str = string.format("%02d",row_index)
        print(str.." " ..require("serpent").line(value))

        row_index = row_index+1
    end
end

local g_chain_flag = {}

local g_calc_count = 0

--设置
function set_zone_value(r,c,zone,value)
    --g_calc_count = g_calc_count + 1
    if zone[r] ~= nil and zone[r][c] ~= nil then
        --如果该格子在前期已经被引爆，则不在加入判断,导致图形不对称也是正常的
        if zone[r][c] == 0 then
            return false 
        end
       zone[r][c] = zone[r][c] - 1
       return true
    end
    return false
end

function is_zone_flag_set(r,c,zone)
  g_calc_count = g_calc_count + 1
  if zone[r] ~= nil and zone[r][c] ~= nil then
      if zone[r][c] == 0 then
          return {true,false}
      end
      return {true,true}
  end
  return {false,false}
end

--左右下
function effect_node_around(oSingleNode,vecZone)
    local effect_node = {}
    --local mapdir = { { 0, -1 }, { 0, 1 }, { 1, 0 } }
    --local mapdir = { {0,-2},{ 0, -1 }, { 0, 1 },{ 0, 2 }, { 1, 0 } ,{ 2, 0 } }
    local mapdir = { {0,-1},{ 0, 1 }, { 0, -2 },{ 0, 2 }, { 1, 0 } ,{ 2, 0 } }
    --local mapdir = { {0,-1},{ 0, 1 }, { 0, -2 },{ 0, 2 },{0,-3},{ 0, 3}, { 1, 0 } ,{ 2, 0 },{3,0} }
    for _, value in pairs(mapdir) do
        local effect_r_index = value[1] + oSingleNode[1]
        local effect_c_index = value[2] + oSingleNode[2]

        local rst = is_zone_flag_set(effect_r_index,effect_c_index,vecZone)
        --if set_zone_value(effect_r_index, effect_c_index, vecZone, 0) then
        if rst[1]== true and rst[2] == true then
            table.insert(effect_node, { effect_r_index, effect_c_index })
        end
    end
    return effect_node
end

function do_chain(vecNode, vecZone, dwChainCount)
    dwChainCount = dwChainCount + 1
    for _, value in pairs(vecNode) do
        --do custom logic,击碎冰块
        set_zone_value(value[1], value[2],vecZone, 0)
        g_chain_flag[value[1]*20 + value[2]] = 1
        -- 如果已经是第三次，不在连锁反应,只处理到这个节点
        if dwChainCount <= 3 then 
            local effect_nodes = effect_node_around(value, vecZone)
            if #effect_nodes ~= 0 then
                do_chain(effect_nodes, vecZone, dwChainCount)
            end
        end
    end
end

function dump_chain_flag(flags)
    local celleffect = {}
    for key,_ in pairs(g_chain_flag) do
        local r = math.floor(key/20)
        local c = key%20
        table.insert(celleffect,{r,c})
    end
    print_zone(celleffect)
end

local first_node = {{5,1}}--,{5,11},{4,10},{4,11}}
local second_node = {{1,10}}
g_chain_flag = {}
g_calc_count = 0
do_chain(first_node,g_veczone,1)
print_zone(g_veczone)
print("calc...."..g_calc_count)
dump_chain_flag(g_chain_flag)
g_chain_flag = {}
g_calc_count = 0
do_chain(second_node,g_veczone,0)
print_zone(g_veczone)
print("calc...."..g_calc_count)
dump_chain_flag(g_chain_flag)


local EIceChainDirConfig = {
    EIce_ChainDir_L = 1,--左边
    EIce_ChainDir_D = 2,--下方
    EIce_ChainDir_R = 3,--右方
}

for i =EIceChainDirConfig.EIce_ChainDir_L,EIceChainDirConfig.EIce_ChainDir_R do
    print(i)
end