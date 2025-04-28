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
        Mobs(string name, int level, int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots);
        ~Mobs();

        int getExpReward() const;
        double getDropRate() const;
        void setExpReward(int expReward);
        void useSkill(string skill, Unit& target); // TEMPORARY
        vector<Item*> dropLoot(); 
        void reset();


};

#endif