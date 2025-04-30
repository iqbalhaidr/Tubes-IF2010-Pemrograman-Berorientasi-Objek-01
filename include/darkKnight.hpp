#ifndef DARKKNIGHT_HPP
#define DARKKNIGHT_HPP

#include "bossMobs.hpp"
#include <string>
using namespace std;

class DarkKnight : public BossMobs {
    public:
        // ctor dtor
        DarkKnight(int level, int expReward, Mobloot& mobLoots);
        ~DarkKnight();
        void updateBasicAttributes() override ;



};

#endif