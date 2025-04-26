#ifndef DemonLord_HPP
#define DemonLord_HPP

#include "bossMobs.hpp"
#include <string>
using namespace std;

class DemonLord : public BossMobs {
    public:
        // ctor dtor
        DemonLord(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots);
        ~DemonLord();



};

#endif