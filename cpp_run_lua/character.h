//
// Created by zhenkai on 2020/4/28.
//

#ifndef CPP_LUA_CHARACTER_H
#define CPP_LUA_CHARACTER_H

#include <iostream>

class Character {
public:
    Character(const char* name, int hp);
    void say(const char* text);
    void heal(Character* character);
    const char* getName() { return name; }
    int getHealth() { return health; }
    void setHealth(int hp) { health = hp; }
    // will be implemented later
//    void interact(Character* character);
private:
    const char* name;
    int health;
};




#endif //CPP_LUA_CHARACTER_H
