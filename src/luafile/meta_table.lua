local meta = {
    __newindex = function(t, key, value)
        print("call __newindex",t, key, value)
        rawset(t, key, value)
    end
}

local test = {}
setmetatable(test, meta)
test.name = "name"
print(test.name)


local test = {}

local meta = {
    __index = function(t, k)
        print("__index", k)
        if rawget(t, k) == nil then
            print("Can't find ".. k)
        end

        return rawget(t, k)
    end,
}

setmetatable(test, meta)

print("test.name1", test.name)
test.name = "hello"
print("test.name2", test.name)

local testformeta = {}

local metatable = {
    __index = {name="meta"},
}

setmetatable(testformeta, metatable)

print("test.name1", testformeta.name)
test.name = "hello"
print("test.name2", testformeta.name)