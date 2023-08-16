-- 打开文件
local file = io.open("call_file_function.lua", "r") -- "r"表示以只读模式打开文件

if file then
    -- 读取文件内容
    local content = file:read("*a") -- "*a"表示读取整个文件内容

    -- 关闭文件
    file:close()

    -- 处理文件内容
    print(content)
    dofile("call_file_function.lua")
else
    print("无法打开文件")
end

