function func_with_march(dwid,string)
    print('string with march')
end

function func_with_march(dwid)
    print('string without march')
end

function func_param()
    print("call")
    return "call"
end

function get_flag()
    return false
end

print("..............")
_ = get_flag() and func_param( func_param())
