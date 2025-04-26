#ifndef MOBS_HPP
#define MOBS_HPP

#include "unit.hpp"
#include "mobloot.hpp"
#include <string>
using namespace std;

class Mobs : public Unit {
    protected:
        int expReward;
        vector<pair<Item*, double>> LootDrop;

    public:
        // ctor dtor
        Mobs(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots);
        ~Mobs();

        int getExpReward() const;
        double getDropRate() const;
        void setExpReward(int expReward);
        void useSkill(string& skill) override; // TEMPORARY
        vector<Item*> dropLoot(); 
        void reset();


};

#endif