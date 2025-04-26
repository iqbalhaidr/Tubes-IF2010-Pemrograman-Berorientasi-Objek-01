#ifndef LICH_HPP
#define LICH_HPP

#include "bossMobs.hpp"
#include <string>
using namespace std;

class Lich : public BossMobs {
    public:
        // ctor dtor
        Lich(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots);
        ~Lich();



};

#endif