
local g_veczone = {
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

function print_zone(vecZone)
    for _,value in pairs(vecZone) do
        print(require("serpent").line(value))
    end
end

local g_chain_flag = {}

local g_calc_count = 0

function set_zone_value(r,c,zone,value)
    g_calc_count = g_calc_count + 1
    if zone[r] ~= nil and zone[r][c] ~= nil then
        --如果该格子在前期已经被引爆，则不在加入判断,导致图形不对称也是正常的
        if zone[r][c] == 0 then
            return false 
        end
       zone[r][c] = 0 
       return true
    end
    return false
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

        --if g_chain_flag[effect_r_index*20 + effect_c_index] == nil then
            if set_zone_value(effect_r_index, effect_c_index, vecZone, 0) then
                table.insert(effect_node, { effect_r_index, effect_c_index })
            end
        --end

        --TODO check valid
    end
    return effect_node
end

function do_chain(vecNode, vecZone, dwChainCount)
    if dwChainCount == 3 then
        return
    end
    dwChainCount = dwChainCount + 1
    for _, value in pairs(vecNode) do
        set_zone_value(value[1], value[2],vecZone, 0)
        g_chain_flag[value[1]*20 + value[2]] = 1
        local effect_nodes = effect_node_around(value, vecZone)
        if #effect_nodes ~= 0 then
            do_chain(effect_nodes, vecZone, dwChainCount)
        end
    end
end
local first_node = {{5,10}}--,{5,11},{4,10},{4,11}}
do_chain(first_node,g_veczone,0)
local second_node = {{1,10}}
print_zone(g_veczone)
print("calc...."..g_calc_count)
do_chain(second_node,g_veczone,0)
print_zone(g_veczone)
print("calc...."..g_calc_count)