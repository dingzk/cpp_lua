//
// Created by zhenkai on 2020/4/28.
//

#include <iostream>
#include <unistd.h>
#include "lua.hpp"

/*
 * Any function registered with Lua must have this same prototype, defined as lua_CFunction in lua.h:
typedef int (*lua_CFunction) (lua_State *L);
 */

static int l_write(lua_State* L) {
    const char * str = lua_tostring(L, 1); // get function argument
    std::cout << str << std::endl;
//    write(STDOUT_FILENO, str, sizeof(str)); // calling C++ function with this argument...
    return 0; // nothing to return!
}

// return sum of value
static int l_sum(lua_State* L) {

    lua_pushnumber(L, lua_tonumber(L, 1) + lua_tonumber(L, 2));

    return 1;
}

//int main(void) {
//    lua_State * L = luaL_newstate();
//    luaL_openlibs(L); // load default Lua libs
//    if (luaL_loadfile(L, "run.lua")) {
//        std::cout << "ERROR load lua file" << std::endl;
//        return 1;
//    }
//    lua_pushcfunction(L, l_write);
//    lua_setglobal(L, "write"); // this is how function will be named in Lua
//
//    lua_pushcfunction(L, l_sum);
//    lua_setglobal(L, "sum");
//
//    lua_pcall(L, 0, 0, 0); // run script
//
//    return 0;
//}