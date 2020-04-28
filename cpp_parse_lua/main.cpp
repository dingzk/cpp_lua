//
// Created by zhenkai on 2020/4/27.
//

#include <iostream>
#include "luascript.h"

int main(void)
{
    LuaScript lo("run.lua");

    std::string s = lo.get<std::string>("hello");

    std::cout << s << std::endl;

}