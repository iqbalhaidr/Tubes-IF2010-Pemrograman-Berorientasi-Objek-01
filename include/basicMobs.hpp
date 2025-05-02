#ifndef BASICMOBS_HPP
#define BASICMOBS_HPP

#include "mobs.hpp"
#include <string>
using namespace std;

class BasicMobs : public Mobs {
    public:
        // ctor dtor
        BasicMobs(string name, int level, int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots);
        virtual ~BasicMobs();

        // void reset();


};

#endif