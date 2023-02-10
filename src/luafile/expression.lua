local mCalcMap ={}
    mCalcMap["+++"] = function(param1,param2,param3,param4) return param1+param2+param3+param4 end
    mCalcMap["++-"] = function(param1,param2,param3,param4) return param1+param2+param3-param4 end
    mCalcMap["++*"] = function(param1,param2,param3,param4) return param1+param2+param3*param4 end
    mCalcMap["++÷"] = function(param1,param2,param3,param4) return param1+param2+param3//param4 end
    mCalcMap["+-+"] = function(param1,param2,param3,param4) return param1+param2-param3+param4 end
    mCalcMap["+--"] = function(param1,param2,param3,param4) return param1+param2-param3-param4 end
    mCalcMap["+-*"] = function(param1,param2,param3,param4) return param1+param2-param3*param4 end
    mCalcMap["+-÷"] = function(param1,param2,param3,param4) return param1+param2-param3//param4 end
    mCalcMap["+*+"] = function(param1,param2,param3,param4) return param1+param2*param3+param4 end
    mCalcMap["+*-"] = function(param1,param2,param3,param4) return param1+param2*param3-param4 end
    mCalcMap["+**"] = function(param1,param2,param3,param4) return param1+param2*param3*param4 end
    mCalcMap["+*÷"] = function(param1,param2,param3,param4) return param1+param2*param3//param4 end
    mCalcMap["+÷+"] = function(param1,param2,param3,param4) return param1+param2//param3+param4 end
    mCalcMap["+÷-"] = function(param1,param2,param3,param4) return param1+param2//param3-param4 end
    mCalcMap["+÷*"] = function(param1,param2,param3,param4) return param1+param2//param3*param4 end
    mCalcMap["+÷÷"] = function(param1,param2,param3,param4) return param1+param2//param3//param4 end
    mCalcMap["-++"] = function(param1,param2,param3,param4) return param1-param2+param3+param4 end
    mCalcMap["-+-"] = function(param1,param2,param3,param4) return param1-param2+param3-param4 end
    mCalcMap["-+*"] = function(param1,param2,param3,param4) return param1-param2+param3*param4 end
    mCalcMap["-+÷"] = function(param1,param2,param3,param4) return param1-param2+param3//param4 end
    mCalcMap["--+"] = function(param1,param2,param3,param4) return param1-param2-param3+param4 end
    mCalcMap["---"] = function(param1,param2,param3,param4) return param1-param2-param3-param4 end
    mCalcMap["--*"] = function(param1,param2,param3,param4) return param1-param2-param3*param4 end
    mCalcMap["--÷"] = function(param1,param2,param3,param4) return param1-param2-param3//param4 end
    mCalcMap["-*+"] = function(param1,param2,param3,param4) return param1-param2*param3+param4 end
    mCalcMap["-*-"] = function(param1,param2,param3,param4) return param1-param2*param3-param4 end
    mCalcMap["-**"] = function(param1,param2,param3,param4) return param1-param2*param3*param4 end
    mCalcMap["-*÷"] = function(param1,param2,param3,param4) return param1-param2*param3//param4 end
    mCalcMap["-÷+"] = function(param1,param2,param3,param4) return param1-param2//param3+param4 end
    mCalcMap["-÷-"] = function(param1,param2,param3,param4) return param1-param2//param3-param4 end
    mCalcMap["-÷*"] = function(param1,param2,param3,param4) return param1-param2//param3*param4 end
    mCalcMap["-÷÷"] = function(param1,param2,param3,param4) return param1-param2//param3//param4 end
    mCalcMap["*++"] = function(param1,param2,param3,param4) return param1*param2+param3+param4 end
    mCalcMap["*+-"] = function(param1,param2,param3,param4) return param1*param2+param3-param4 end
    mCalcMap["*+*"] = function(param1,param2,param3,param4) return param1*param2+param3*param4 end
    mCalcMap["*+÷"] = function(param1,param2,param3,param4) return param1*param2+param3//param4 end
    mCalcMap["*-+"] = function(param1,param2,param3,param4) return param1*param2-param3+param4 end
    mCalcMap["*--"] = function(param1,param2,param3,param4) return param1*param2-param3-param4 end
    mCalcMap["*-*"] = function(param1,param2,param3,param4) return param1*param2-param3*param4 end
    mCalcMap["*-÷"] = function(param1,param2,param3,param4) return param1*param2-param3//param4 end
    mCalcMap["**+"] = function(param1,param2,param3,param4) return param1*param2*param3+param4 end
    mCalcMap["**-"] = function(param1,param2,param3,param4) return param1*param2*param3-param4 end
    mCalcMap["***"] = function(param1,param2,param3,param4) return param1*param2*param3*param4 end
    mCalcMap["**÷"] = function(param1,param2,param3,param4) return param1*param2*param3//param4 end
    mCalcMap["*÷+"] = function(param1,param2,param3,param4) return param1*param2//param3+param4 end
    mCalcMap["*÷-"] = function(param1,param2,param3,param4) return param1*param2//param3-param4 end
    mCalcMap["*÷*"] = function(param1,param2,param3,param4) return param1*param2//param3*param4 end
    mCalcMap["*÷÷"] = function(param1,param2,param3,param4) return param1*param2//param3//param4 end
    mCalcMap["÷++"] = function(param1,param2,param3,param4) return param1//param2+param3+param4 end
    mCalcMap["÷+-"] = function(param1,param2,param3,param4) return param1//param2+param3-param4 end
    mCalcMap["÷+*"] = function(param1,param2,param3,param4) return param1//param2+param3*param4 end
    mCalcMap["÷+÷"] = function(param1,param2,param3,param4) return param1//param2+param3//param4 end
    mCalcMap["÷-+"] = function(param1,param2,param3,param4) return param1//param2-param3+param4 end
    mCalcMap["÷--"] = function(param1,param2,param3,param4) return param1//param2-param3-param4 end
    mCalcMap["÷-*"] = function(param1,param2,param3,param4) return param1//param2-param3*param4 end
    mCalcMap["÷-÷"] = function(param1,param2,param3,param4) return param1//param2-param3//param4 end
    mCalcMap["÷*+"] = function(param1,param2,param3,param4) return param1//param2*param3+param4 end
    mCalcMap["÷*-"] = function(param1,param2,param3,param4) return param1//param2*param3-param4 end
    mCalcMap["÷**"] = function(param1,param2,param3,param4) return param1//param2*param3*param4 end
    mCalcMap["÷*÷"] = function(param1,param2,param3,param4) return param1//param2*param3//param4 end
    mCalcMap["÷÷+"] = function(param1,param2,param3,param4) return param1//param2//param3+param4 end
    mCalcMap["÷÷-"] = function(param1,param2,param3,param4) return param1//param2//param3-param4 end
    mCalcMap["÷÷*"] = function(param1,param2,param3,param4) return param1//param2//param3*param4 end
    mCalcMap["÷÷÷"] = function(param1,param2,param3,param4) return param1//param2//param3//param4 end

print(mCalcMap["+++"](1,2,2,3))
a = os.clock()
for i=1,100000 do
    local j = (mCalcMap["***"](1,2,2,3))
end
b= os.clock()
print (b-a)

a1 = os.clock()
for i=1,100000 do
    local j = load("return 1*2*2*3")
end
b1= os.clock()
print (b1-a1)



