require("class_define")

Stack = class()

function Stack:Ctor()
    self.dw_ele_count = 0
    self._stack = {}
    print(".....")
end

function Stack:push(item)
    self.dw_ele_count = self.dw_ele_count + 1
    table.insert(self._stack, item) 
end

function Stack:pop()
    if self.dw_ele_count == 0 then
        return nil
    end
    self.dw_ele_count = self.dw_ele_count - 1
    return table.remove(self._stack)
end

function Stack:top()
    return self._stack[#self._stack]    
end

function Stack:GetEleCount()
    return self.dw_ele_count
end

origin_stack = Stack:new()
local str_calc = {123,"+",3,"*",33,"+",1}

local print_str = table.concat(str_calc)
print(print_str)

function is_calc_op_symbol(str)
    return str == "+" or str == "-" or str == "*" or str == "/"
end

function is_op_pri(f,s)
    if f == "*" or "/" then
        if s == "+" or s == "-" then
            return true
        end
    end
    return false
end

final_stack = Stack:new()
temp_stack = Stack:new()

function do_back(str_calc)
    local systack = Stack:new()
    for _,val in pairs(str_calc) do
        repeat
            if not is_calc_op_symbol(val) then
                final_stack:push(val)
                print("push number to final:"..val)
            else
                local op_tmp_tab = {}

                while(true) do
                    local _top = systack:top() 
                    if _top == nil then
                        print("add op to final"..val)
                        systack:push(val)
                        break
                    end
                    print("....."..val.."   top:".._top)
                    
                    local tmp_table = {}
                    while(true) do
                        --os.execute("sleep 1")
                        if is_calc_op_symbol(_top) and not is_op_pri(val,_top) then
                            _top = final_stack:pop()
                            print(_top)
                            table.insert(tmp_table,_top)
                        else
                            final_stack:push(val)
                            for _,t in pairs(tmp_table) do
                                final_stack:push(t)
                            end
                            break
                        end
                     end
                     break
                end
            end
        until true
    end

end


do_back(str_calc)

print(".............................")
for _,v in pairs(final_stack._stack) do
    print(v)
end
print(".............................")
print(final_stack:GetEleCount())


function do_back_calc(oStack)
    backStack = Stack:new()
    while(oStack:top())
    do
            print("resver"..oStack:top())
            backStack:push(oStack:pop())
    end
    return backStack
end

backStack = do_back_calc(final_stack)
--backStack = final_stack
--
print("after calc.....................")

local print_str1 = table.concat(backStack._stack)
print(print_str1)

local param1 = 0
local param2 = 0
print("----------------------")
while(backStack:top())
do
    print("top"..backStack:top())
    param1 = backStack:pop()
    param2 = backStack:pop()
    param3 = backStack:pop()

    print("p1:"..param1.." p2:"..param2.." p3:"..param3)
    if param3 == "+" then
        param1 = param1 + param2
    elseif param3 == "-" then
        param1 = param1 - param2
    elseif param3 == "*" then
        param1 = param1 * param2
    elseif param3 == "/" then
        param1 = param1//param2
    end
    print("push rst"..param1)
    backStack:push(param1)
    if backStack:GetEleCount() == 1 then
        break
    end
end











