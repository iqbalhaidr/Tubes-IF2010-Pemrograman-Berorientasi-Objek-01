#ifndef OGRE_HPP
#define OGRE_HPP

#include "bossMobs.hpp"
#include <string>
using namespace std;

class Ogre : public BossMobs {
    public:
        // ctor dtor
        Ogre(int level, int expReward, Mobloot& mobLoots);
        ~Ogre();
        void updateBasicAttributes() override;
        // void useSkill(string skill, Unit& target) override{}


};

#endif