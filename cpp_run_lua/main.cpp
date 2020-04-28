//
// Created by zhenkai on 2020/4/28.
//

#include <iostream>
#include "lua.hpp"
#include "character.h"
#include "luawrapper.hpp"

/*
 * player = Character.new("Hero", 100)
 * player:getHealth()
 * Using luaW_check(L, 1) you can get player object and use it as usual in C++.
 */

Character* Character_new(lua_State* L) {
    const char* name = luaL_checkstring(L, 1);
    int hp = luaL_checknumber(L, 2);
    return new Character(name, hp);
}

int Character_getName(lua_State* L) {
    Character* character = luaW_check<Character>(L, 1);
    lua_pushstring(L, character->getName());
    return 1;
}

int Character_getHealth(lua_State* L) {
    Character* character = luaW_check<Character>(L, 1);
    lua_pushnumber(L, character->getHealth());
    return 1;
}

int Character_free(lua_State* L) {
    Character* character = luaW_check<Character>(L, 1);
    if (character != NULL) {
        delete character;
    }
    return 0;
}

/*
 * I’ll use checknumber instead of tonumber from now on. It’s basically the same but it will throw error message if something goes wrong.
 */

int Character_setHealth(lua_State* L) {
    Character* character = luaW_check<Character>(L, 1);
    int hp = luaL_checknumber(L, 2);
    character->setHealth(hp);
    return 0;
}

/*
 * ref: http://lua-users.org/wiki/BindingCodeToLua
 */

static luaL_Reg Character_table[] = {
        { NULL, NULL }
};

static luaL_Reg Character_metatable[] = {
        { "getName", Character_getName },
        { "getHealth", Character_getHealth },
        { "setHealth", Character_setHealth },
//        { "free", Character_free },
        { NULL, NULL }
};

static int luaopen_Character(lua_State* L) {
    luaW_register<Character>(L, "Character", Character_table, Character_metatable, Character_new);
    return 1;
}


/*
 * Important: you need to call this before calling luaL_loadfile because Lua doesn’t know about your class and it may think your code is incorrect.
 */

int main(void) {

    lua_State * L = luaL_newstate();
    luaopen_Character(L);

    luaL_openlibs(L); // load default Lua libs

//    if (luaL_loadfile(L, "character.lua")) {
//        std::cout << "ERROR load lua file" << std::endl;
//        return 1;
//    }
//    lua_pcall(L, 0, 0, 0); // run script

    luaL_dofile(L, "character.lua");

    lua_close(L); // be careful double free


    return 0;
}



