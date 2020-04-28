
#include <iostream>
#include "lua.hpp"

//在Lua Code中注册的函数
int  sum(lua_State *L)
{
    int top =lua_gettop(L);
    int sum =0;
    for(size_t t=top;t>0;t--)
    {
        int lnum =lua_tonumber(L,t);
        sum+=lnum;
    }
    lua_pushnumber(L,sum);
    return 1;
}
//通过lua_pushcclosure()方法来在Lua Code中注册C函数
//lua_pushcclosure()函数是Lua C API提供注册C函数最基础的。其他注册方式都是在该函数上面拓展的。
//typedef int (*lua_CFunction) (lua_State *L); 为注册C函数的标准形式
// lua_pushcclosure() 中参数n为提供闭包upvalues值的数量
void register_sum(lua_State *L)
{
    lua_settop(L, 0);
//    int n =0;
//    lua_pushcclosure (L, sum,  n);

    // equal to
    lua_pushcfunction(L, sum);
    lua_setglobal(L, "sum");
}


//在Lua Code中注册的函数
int  sum_closure(lua_State *L)
{
    //到该函数被调用时,可以通过lua_upvalueindex()函数获取到该函数的closure
    int c1 = (int)lua_tonumber(L, lua_upvalueindex(1));
    int c2 = (int)lua_tonumber(L, lua_upvalueindex(2));
    int top = lua_gettop(L);
    int sum = c1 + c2;
    for (size_t t = top; t > 0; t--)
    {
        int lnum =lua_tonumber(L,t);
        sum += lnum;
    }
    //把结果值压入虚拟栈返回
    lua_pushnumber(L, sum);
    return 1;
}
//提供upvalues
void register_sum_closure(lua_State *L)
{
    lua_settop(L,0);
    //与sum_closure()函数管理的closure管理的值
    lua_pushnumber(L, 100);
    lua_pushnumber(L, 2000);
    int n = 2; //指定与sum_closure()函数管理的upvalue数量
    lua_pushcclosure (L, sum_closure,  n);

    lua_setglobal(L,"sum_closure");
}


int main(void)
{
    lua_State *L = luaL_newstate();

    luaL_openlibs(L); // load default Lua libs

    register_sum(L);

    register_sum_closure(L);


    luaL_dofile(L, "test.lua");

    lua_close(L);

    return 0;

}



