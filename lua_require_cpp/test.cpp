//
// Created by zhenkai on 2020/4/28.
//

// g++ -shared -fPIC -o motan.so test.cpp  -L../lib -L/data1/apache2/htdocs/LuaJIT/src/ -lluajit -Wl,-rpath,../lib:/data1/apache2/htdocs/LuaJIT/src/ -I. -I /data1/apache2/htdocs/LuaJIT/src/

#include "test.h"

extern "C" {

#if !defined(LUA_VERSION_NUM) || LUA_VERSION_NUM < 502
/* Compatibility for Lua 5.1 and older LuaJIT.
 *
 * compat_luaL_setfuncs() is used to create a module table where the functions
 * have json_config_t as their first upvalue. Code borrowed from Lua 5.2
 * source's luaL_setfuncs().
 */
static void compat_luaL_setfuncs(lua_State *l, const luaL_Reg *reg, int nup)
{
    int i;

    luaL_checkstack(l, nup, "too many upvalues");
    for (; reg->name != NULL; reg++)
    {  /* fill the table with given functions */
        for (i = 0; i < nup; i++)  /* copy upvalues to the top */
            lua_pushvalue(l, -nup);
        lua_pushcclosure(l, reg->func, nup);  /* closure with those upvalues */
        lua_setfield(l, -(nup + 2), reg->name);
    }
    lua_pop(l, nup);  /* remove upvalues */
}
#else
#define compat_luaL_setfuncs(L, reg, nup) luaL_setfuncs(L, reg, nup)
#endif

int client_init(lua_State *L)
{
    lua_pushstring(L, "this is client_init");

    return 1;
}

int caller_init(lua_State *L)
{
    lua_pushstring(L, "this is caller_init");

    return 1;
}

int caller_add(lua_State *L)
{
    lua_pushstring(L, "this is caller_add");

    return 1;
}

int caller_do(lua_State *L)
{
    lua_pushstring(L, "this is caller_do");

    return 1;
}

int luaopen_motan(lua_State *L)
{
    luaL_Reg reg[] = {
            {"client_init", client_init},
            {"caller_init", caller_init},
            {"caller_add",  caller_add},
            {"caller_do",   caller_do},
            {NULL, NULL}
    };

    lua_newtable(L);

    luaL_setfuncs(L, reg, 0);

    lua_pushlightuserdata(L, NULL);
    lua_setfield(L, -2, "null");

    /* Set other fields */
    lua_pushliteral(L, "motan");
    lua_setfield(L, -2, "_NAME");
    lua_pushliteral(L, "0.0.1");
    lua_setfield(L, -2, "_VERSION");

    return 1;
}

}