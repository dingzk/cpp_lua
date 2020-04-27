#include <stdio.h>
#include "lua.hpp"

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

// In Lua 5.0 reference manual is a table traversal example at page 29.
void PrintTable(lua_State *L)
{
    lua_pushnil(L);

    while(lua_next(L, -2) != 0)
    {
        if(lua_isstring(L, -1))
            printf("%s = %s\n", lua_tostring(L, -2), lua_tostring(L, -1));
        else if(lua_isnumber(L, -1))
            printf("%s = %d\n", lua_tostring(L, -2), lua_tonumber(L, -1));
        else if(lua_istable(L, -1))
            PrintTable(L);

        lua_pop(L, 1);
    }
}

/*
int main(void)
{
    lua_State *L = lua_open();

    // Load file.
    if(luaL_loadfile(L, "run.lua") || lua_pcall(L, 0, 0, 0))
    {
        printf("Cannot run file\n");
        return 1;
    }

    // Print table contents.
    lua_getglobal(L, "level1");
    PrintTable(L);

    // Print music field.
    printf("total num %d\n", lua_gettop(L));
    printf("\n get pointer %p\n", lua_topointer(L, -1));

    lua_pushstring(L, "music");
    lua_gettable(L, -2);
    printf("total num %d\n", lua_gettop(L));
    printf("\n get pointer %s\n", lua_tostring(L, -1));


    lua_getglobal(L, "hello");
    printf("total num %d\n", lua_gettop(L));
    printf("\n get pointer %s\n", lua_tostring(L, -1));

    printf("total num %d\n", lua_gettop(L));


//
//    if(lua_isstring(L, -1))
//        printf("\nlevel1.music = %s\n", lua_tostring(L, -1));
//
//    printf("\n get pointer %p\n", lua_topointer(L, -1));
//
//    lua_settop(L, 0); // reset stack
//    printf("total num %d\n", lua_gettop(L));

    lua_close(L);

    return 0;
}
 */