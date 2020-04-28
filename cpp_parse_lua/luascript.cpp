//
// Created by zhenkai on 2020/4/27.
//

#include "luascript.h"

LuaScript::LuaScript(const std::string& filename) {
    L = luaL_newstate();
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) {
        std::cout << "Error: script not loaded (" << filename << ")" <<std::endl;
        L = 0;
    }
}

LuaScript::~LuaScript() {
    if(L) lua_close(L);
}

void LuaScript::printError(const std::string& variableName, const std::string& reason) {
    std::cout << "Error: can't get [" << variableName << "]. " << reason << std::endl;
}

// c function
static int foo (lua_State *L) {
    int n = lua_gettop(L);    /* number of arguments */
    lua_Number sum = 0;
    int i;
    for (i = 1; i <= n; i++) {
        if (!lua_isnumber(L, i)) {
            lua_pushstring(L, "incorrect argument");
            lua_error(L);
        }
        sum += lua_tonumber(L, i);
    }
    lua_pushnumber(L, sum/n);        /* first result */
    lua_pushnumber(L, sum);         /* second result */
    return 2;                   /* number of results */
}

/*
 * Any function registered with Lua must have this same prototype, defined as lua_CFunction in lua.h:
typedef int (*lua_CFunction) (lua_State *L);
 */

// In Lua 5.0 reference manual is a table traversal example at page 29.
void LuaScript::printTable(lua_State *L) {
    lua_pushnil(L);
    while(lua_next(L, -2) != 0)
    {
        if(lua_isstring(L, -1))
            printf("%s = %s\n", lua_tostring(L, -2), lua_tostring(L, -1));
        else if(lua_isnumber(L, -1))
            printf("%s = %d\n", lua_tostring(L, -2), lua_tonumber(L, -1));
        else if(lua_istable(L, -1))
            printTable(L);

        lua_pop(L, 1);
    }
}