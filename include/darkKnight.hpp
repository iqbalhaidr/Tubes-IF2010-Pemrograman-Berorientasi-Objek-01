#ifndef DARKKNIGHT_HPP
#define DARKKNIGHT_HPP

#include "bossMobs.hpp"
#include <string>
using namespace std;

class DarkKnight : public BossMobs {
    private:
        void updateBasicAttributes() override;
    public:
        // ctor dtor
        DarkKnight(int level, int expReward, Mobloot& mobLoots);
        ~DarkKnight();



};

#endif