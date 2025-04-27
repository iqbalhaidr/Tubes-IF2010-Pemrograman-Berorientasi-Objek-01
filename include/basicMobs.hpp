#ifndef BASICMOBS_HPP
#define BASICMOBS_HPP

#include "mobs.hpp"
#include <string>
using namespace std;

class BasicMobs : public Mobs {
    public:
        // ctor dtor
        BasicMobs(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots);
        ~BasicMobs();

        void reset();


};

#endif