#ifndef GOBLIN_HPP
#define GOBLIN_HPP

#include "basicMobs.hpp"
#include <string>
using namespace std;

class Goblin : public BasicMobs {
    public:
        // ctor dtor
        Goblin(int level, int expReward, Mobloot& mobLoots);
        ~Goblin();
        void updateBasicAttributes() override ;


};

#endif