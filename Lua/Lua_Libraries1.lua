Lua_Labraries = {}

function Lua_Labraries:new(o)
    o = o or {}
    self.__index = self
    setmetatable(o, self)
    return o
end

--给实例添加方法
function Lua_Labraries:AddFunction(funname, fun)
    self[funname] = fun
end

--给实例添加元素
function Lua_Labraries:AddElement(elename, element)
    self[elename] = element
end

--例:
--给i实例添加方法
i = Lua_Labraries:new()
i:AddFunction('iprint', function()
    print("i AddFunction!\n\r")
end)
i.iprint()

--给i实例添加元素
i:AddElement('ielement', 'lz')
print(i.ielement)
