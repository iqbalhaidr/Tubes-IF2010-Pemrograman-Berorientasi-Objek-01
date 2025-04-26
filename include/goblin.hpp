#ifndef GOBLIN_HPP
#define GOBLIN_HPP

#include "basicMobs.hpp"
#include <string>
using namespace std;

class Goblin : public BasicMobs {
    public:
        // ctor dtor
        Goblin(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int healValue);
        ~Goblin();



};

#endif