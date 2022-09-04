function GetFunInfo()
    local info = debug.getinfo(3, "Sln")
    if not info then
        return "", "", 0
    end
    return info.short_src or "", info.name or "[base function]", info.currentline or 0
end

function test2()
    print(GetFunInfo())
end

function test1()
    test2()
end

test1()
