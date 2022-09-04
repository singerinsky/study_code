print(tostring(str))

a = os.clock()
local s = ''
for i = 1,300000 do
s = s .. 'a'
end
b = os.clock()
print(b-a)


c = os.clock()
local array_str = {}
for i = 1,300000 do
    array_str[#array_str + 1] = 'a'
end
d = os.clock()
print(d-c)


