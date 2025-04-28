#ifndef LICH_HPP
#define LICH_HPP

#include "bossMobs.hpp"
#include <string>
using namespace std;

class Lich : public BossMobs {
    public:
        // ctor dtor
        Lich(int level, int expReward, Mobloot& mobLoots);
        ~Lich();
        void updateBasicAttributes() override ;



};

#endif