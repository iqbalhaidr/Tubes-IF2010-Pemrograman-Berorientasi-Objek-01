#ifndef STATS_HPP
#define STATS_HPP

#include <string>
using namespace std;

class Stats {
    private:
        int strength;
        int agility;
        int intelligence;
    public:
        // ctor dtor
        Stats(int strength, int agility, int intelligence);
        ~Stats();

        // setter getter
        int getStrength() const;
        int getAgility() const;
        int getIntelligence() const;
        void setStrength(int strength);
        void setAgility(int agility);
        void setIntelligence(int intelligence);
};

#endif