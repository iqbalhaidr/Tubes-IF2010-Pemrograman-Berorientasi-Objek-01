#ifndef GOBLIN_HPP
#define GOBLIN_HPP

#include "basicMobs.hpp"
#include <string>
using namespace std;

class Goblin : public BasicMobs {
    private:
        void updateBasicAttributes() override;
    public:
        // ctor dtor
        Goblin(int level, int expReward, Mobloot& mobLoots);
        ~Goblin();


};

#endif