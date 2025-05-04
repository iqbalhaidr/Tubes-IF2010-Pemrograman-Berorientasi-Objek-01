#ifndef SLIME_HPP
#define SLIME_HPP

#include "basicMobs.hpp"
#include <string>
using namespace std;

class Slime : public BasicMobs {
    private:
        void updateBasicAttributes() override;
    public:
        // ctor dtor
        Slime(int level, int expReward, Mobloot& mobLoots);
        ~Slime();


};

#endif