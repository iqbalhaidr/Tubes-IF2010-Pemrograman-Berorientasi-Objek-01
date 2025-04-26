#ifndef DARKKNIGHT_HPP
#define DARKKNIGHT_HPP

#include "bossMobs.hpp"
#include <string>
using namespace std;

class DarkKnight : public BossMobs {
    public:
        // ctor dtor
        DarkKnight(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots);
        ~DarkKnight();



};

#endif