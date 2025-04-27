#ifndef OGRE_HPP
#define OGRE_HPP

#include "bossMobs.hpp"
#include <string>
using namespace std;

class Ogre : public BossMobs {
    public:
        // ctor dtor
        Ogre(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots);
        ~Ogre();



};

#endif