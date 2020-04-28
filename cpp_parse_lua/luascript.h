//
// Created by zhenkai on 2020/4/27.
//

#ifndef MOTAN_CPP_LUASCRIPT_H
#define MOTAN_CPP_LUASCRIPT_H

#include <string>
#include <iostream>
#include "lua.hpp"

class LuaScript
{
public:
    explicit LuaScript(const std::string& filename);
    ~LuaScript();
    void printError(const std::string& variableName, const std::string& reason);
    void printTable(lua_State *L);

    template<typename T>
    T get(const std::string& variableName) {
        if(!L) {
            printError(variableName, "Script is not loaded");
            return lua_getdefault<T>();
        }

        T result;
        if(lua_gettostack(variableName)) { // variable succesfully on top of stack
            result = lua_get<T>(variableName);
        } else {
            result = lua_getdefault<T>();
        }

        lua_pop(L, level + 1); // pop all existing elements from stack

        return result;
    }

    // TODO 把指定的内容放到堆栈上
    bool lua_gettostack(const std::string& variableName) {
        level = 0;
        lua_getglobal(L, variableName.c_str());

        return true;
    }

    // Generic get
    template<typename T>
    T lua_get(const std::string& variableName) {
        lua_getdefault<T>(variableName);
    }

    // Generic default get
    template<typename T>
    T lua_getdefault(const std::string& variableName = "") {
        return 0;
    }

private:
    lua_State* L;
    int level;

};

// default get
template<>
inline std::string LuaScript::lua_getdefault(const std::string& variableName) {
    return "null";
}

// bool get
template <>
inline bool LuaScript::lua_get(const std::string& variableName) {
    return (bool)lua_toboolean(L, -1);
}

// float get
template <>
inline float LuaScript::lua_get(const std::string& variableName) {
    if(!lua_isnumber(L, -1)) {
        printError(variableName, "Not a number");
    }

    return (float)lua_tonumber(L, -1);
}

// int get
template <>
inline int LuaScript::lua_get(const std::string& variableName) {
    if(!lua_isnumber(L, -1)) {
        printError(variableName, "Not a number");
    }

    return (int)lua_tonumber(L, -1);
}

// string get
template <>
inline std::string LuaScript::lua_get(const std::string& variableName) {
    std::string s = "null";
    if(lua_isstring(L, -1)) {
        s = std::string(lua_tostring(L, -1));
    } else {
        printError(variableName, "Not a string");
    }

    return s;
}




#endif //MOTAN_CPP_LUASCRIPT_H
