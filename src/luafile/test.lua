local my = require "libluatestlib"
print(my.my_add())


local veczone = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
}

--左右下
function get_node_around(oSingleNode,vecZone)
   local mapdir = {{-1,0},{0,1},{1,0}} 
    for _,value in pairs(mapdir) do
        value[1] = value[1] + oSingleNode[1]
        value[2] = value[2] + oSingleNode[2]
        --TODO check valid
    end
    print("node data"..require("serpent").line(oSingleNode))
    print(require("serpent").block(mapdir))
end

function do_chain(vecNode,vecZone,dwChainCount)
    for _,value in pairs(vecNode) do
        get_node_around(value)
    end
end

do_chain({1,5},veczone,1)