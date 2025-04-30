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
        Mobs(string name, int strength, int agility, int intelligence, int level, int expReward, Mobloot& mobLoots);
        virtual ~Mobs();

        int getExpReward() const;
        void setExpReward(int expReward);
        vector<Item*> dropLoot(); 
        void reset();


};

#endif