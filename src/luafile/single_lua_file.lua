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

local function check_more_than_one(array,size)
   local count = 0
   local all_one = true
   local lines = {}
   for i = 0, size - 1, 1 do
    all_one = true
    local celltocheck = {}
    for j = 0, size - 1, 1 do
        if array[i*size + j] ==0 then
            all_one = false
            break
        end
        celltocheck[i*size+j] = 1
    end
    if all_one == true then
        print("1")
        count = count + 1
        table.insert(lines,celltocheck)
    end
   end 

   for i = 0, size - 1, 1 do
    local all_one = true
    for j = 0, size - 1, 1 do
        if array[i + size * j] ==0 then
            all_one = false
            break
        end
    end
    if all_one == true then
        print("2")
        count = count + 1
    end
   end 

   all_one = true
   for i =0 ,size -1 ,1 do
        if array[i*size + i] ==0 then
            all_one = false;
            break
        end
   end
   if all_one == true then
       print("3")
       count = count + 1
   end

   all_one = true
   for i =0 ,size -1 ,1 do
        if array[(size -i -1)*size + i] ==0 then
            all_one = false;
            break
        end
   end
   if all_one == true then
       print("4")
       count = count + 1
   end

   if count ~= 1 then
       assert("failed.")
       return false
   end
   return true 
end


local  ECellValue= {
    eFalse = 0,--空的值
    eTrue = 1,--有值
}

local ELineDir = {
    eRow = 0,--行
    eCol = 1,--列
    eLTDiagonal = 2,--左上对角线
    eRTDiagonal = 3,--右上对角线
}

local EMthSize = {
    eThree = 3,
    eFour = 4,
    eFive = 5,
}

function shuffle_fill_data(array)
    local shuffledArray = {}
    while #array > 0 do
        local rand = math.random(#array)
        table.insert(shuffledArray, array[rand])
        table.remove(array, rand)
    end
    return shuffledArray
end

local function init_matirx(size)
    local matrixArray = {}
    for i = 1, size, 1 do
        for j = 1, size, 1 do
            --local flag = math.random(ECellValue.eFalse,ECellValue.eTrue)
            matrixArray[(i-1)*size+j-1] = 0
        end
    end
    --print_mth(matrixArray,size)
    -- 生成行的方式,要保证均匀分布
    local genTypeRandLib = {}
    for i = 1, size, 1 do
        table.insert(genTypeRandLib,ELineDir.eRow)
        table.insert(genTypeRandLib,ELineDir.eCol)
    end
    table.insert(genTypeRandLib,ELineDir.eRTDiagonal)
    table.insert(genTypeRandLib,ELineDir.eLTDiagonal)
    
    local cellSelected = {}
    --local eLineType = math.random(ELineDir.eRow,ELineDir.eRTDiagonal)
    local eLineType = genTypeRandLib[math.random(1,#genTypeRandLib)]
    print("build type"..eLineType)
    -- 生成行
    if eLineType == ELineDir.eRow then
        local rowSelect = math.random(0,size - 1)
        for i = 0, size - 1 do
           local dwIndex = size * rowSelect + i 
           cellSelected[dwIndex] = 1
           matrixArray[dwIndex] = 1
        end
    elseif eLineType == ELineDir.eCol then
        local colSelect = math.random(0,size - 1)
        for i = 0, size - 1 do
           local dwIndex = size * i+ colSelect 
           cellSelected[dwIndex] = 1
           matrixArray[dwIndex] = 1
        end
    elseif eLineType == ELineDir.eLTDiagonal then 
        for i = 0, size - 1 do
           local dwIndex = size * i+ i  
           cellSelected[dwIndex] = 1
           matrixArray[dwIndex] = 1
        end
    elseif eLineType == ELineDir.eRTDiagonal then
        for i = size, 1,-1 do
           local dwIndex = (size - 1) * i  
           cellSelected[dwIndex] = 1
           matrixArray[dwIndex] = 1
        end
    end
    -- 填入数据
    local MatixFillData = {}
    MatixFillData[3] = {1, 1, 1, 1, 0, 0}
    MatixFillData[4] = {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}
    MatixFillData[5] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}
    --MatixFillData[5] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

    local fillData = MatixFillData[size]
    if fillData == nil then
        print("error size of matrix")
    end
   
    local shuffle_data = shuffle_fill_data(fillData) 
   
    for index, value in pairs(matrixArray) do
        if cellSelected[index] == nil and #shuffle_data> 0 then
            matrixArray[index] = table.remove(shuffle_data,1)         
        end
    end
    return cellSelected,matrixArray
end

local function check_matirx_row_col(matrixArray,cellSelected,size,index_calc_func)
    local rows_cols_to_without_zero = {}
    for i = 0, size - 1, 1 do
        local zero_flag = false
        local is_match_result = true 
        local cellToFix = {}
        for j = 0, size - 1, 1 do
            --local dwIndexToCheck = i * size + j
            local dwIndexToCheck = index_calc_func(i,j,size)
            if matrixArray[dwIndexToCheck] == 0 then
                zero_flag = true
                is_match_result = false
                break
            end
            if cellSelected[dwIndexToCheck] == nil then
                is_match_result = false
                table.insert(cellToFix,dwIndexToCheck)
            end
        end
        --有重复的
        if zero_flag == false and is_match_result == false then
            table.insert(rows_cols_to_without_zero,cellToFix)
            local indexToSetZero = cellToFix[math.random(1,#cellToFix)]
            matrixArray[indexToSetZero] = 0
        end
    end 
    return rows_cols_to_without_zero
end

local function check_matirx_Diagonal(matrixArray,cellSelected,size,index_calc_func)
    local zero_flag = false
    local is_match_result = true 
    local cellToFix = {}
    for i = 0, size - 1, 1 do
      -- local dwIndexToCheck = size*(size - 1) +1+i 
       local dwIndexToCheck = index_calc_func(i,size)
       if matrixArray[dwIndexToCheck] == 0 then
           zero_flag = true
           is_match_result = false
           break
       end
       if cellSelected[dwIndexToCheck] == nil then
            is_match_result = false
            table.insert(cellToFix,dwIndexToCheck)
       end
    end
    if zero_flag == false and is_match_result == false then
            local indexToSetZero = cellToFix[math.random(1,#cellToFix)]
            matrixArray[indexToSetZero] = 0
            return cellToFix
    end
end

-- Matrix
local function build_mth(size)
    if size == nil or size < 1 or size > 5 then
        print("error")
        return 
    end

    local cellSelected,matrixArray = init_matirx(size)
    if cellSelected == nil or matrixArray == nil then
        print("error")
        return
    end

    local zero_flag = false
    local is_match_result = true 
    local cellToFix = {}

    print("before check ................")
    --check row 
    check_matirx_row_col(matrixArray,cellSelected,size,function(i,j,size)
        return i*size+j
    end)
    -- check col
    check_matirx_row_col(matrixArray,cellSelected,size,function(i,j,size)
        return j*size+i
    end)
    --check lt cornor
    check_matirx_Diagonal(matrixArray,cellSelected,size,function(i,size)
       return i*size +i 
    end)
    --check rt cornor
    check_matirx_Diagonal(matrixArray,cellSelected,size,function(i,size)
        return size*(size - i - 1 ) +i 
    end)
    
    local rst = check_more_than_one(matrixArray,size)
    if rst == false then
        print_mth(matrixArray,size)
        print("error")
        assert(false)
    end

    print_mth(matrixArray,size)
    local cells_string = ""
    for index, value in pairs(cellSelected) do
        cells_string = index.."-"..cells_string 
       if matrixArray[index] == 0 then
           print("errorooooooooooooooooooooooooo")
           assert(false)
       end
    end
    print(cells_string)

    return matrixArray
end

local value_int = 0

if value_int ==0 then
	print(" not value_int is true")
end

local function get_right_anwser(all_mat,size)
    local right_anwer = {}
    for i =0,size -1 do
        local all_1 =true 
        local queue = {}
        for j =0,size -1 do
            if all_mat[i*size+ j] == 0 then
                all_1 = false
                break
            end
            table.insert(queue,i*size+j)
        end    
        if all_1 == true then
           table.insert(right_anwer,queue) 
        end
    end
end

local function cmp_result(all_mat,user_mat)


end
function GetTableNum(t)
    local dwCount = 0
    for _ in pairs(t or {}) do
        dwCount = dwCount + 1
    end
    return dwCount
end

function GetTableValue(t)
    local keySet = {}
    local n = 0
    for k, v in pairs(t) do
        n = n + 1
        keySet[n] = v
    end
    return keySet
end


local table_test= {}
table_test[0] =0 
table_test[1] = 1
table_test[2] =2 
table_test[3] =3 
table_test[4] =4
table_test[5] =5 
table_test[6] =6 


local m= {}
local nu = GetTableNum(table_test)
for i = 0, nu-1, 1 do
	table.insert(m,table_test[i])
end

for i,v in pairs(m)do
	print(i..":"..v)
end



for i = 1, 100000, 1 do
    --print("=========================================="..i)
    --build_mth(5)
end

