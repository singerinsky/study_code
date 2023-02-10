
local m = {_TYPENAME = "class"}
function m:new(...)
    local t = {}
    setmetatable(t, { __index = self })
    if t.Ctor then
        t:Ctor(...)
    end
    return t
end

m.__index = m

function class(f)
    return setmetatable({}, {__index = f or m})
end

function typeof(var)
    local _type = type(var)
    if (_type ~= "table" and _type ~= "userdata") then
        return _type
    end
    if var._TYPENAME then
        return var._TYPENAME
    end
    return _type
end

print("load class define")
