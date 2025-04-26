#ifndef BOSSMOBS_HPP
#define BOSSMOBS_HPP

#include "mobs.hpp"
#include <string>
using namespace std;

class BossMobs : public Mobs {
    protected:
        bool onRage;
    public:
        // ctor dtor
        BossMobs(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int expReward);
        ~BossMobs();
        bool isOnRage() const { return onRage; }
        void reset();


};

#endif