#ifndef ORC_HPP
#define ORC_HPP

#include "basicMobs.hpp"
#include <string>
using namespace std;

class Orc : public BasicMobs {
    public:
        // ctor dtor
        Orc(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots);
        ~Orc();



};

#endif