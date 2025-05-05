#ifndef OGRE_HPP
#define OGRE_HPP

#include "bossMobs.hpp"
#include <string>
using namespace std;

class Ogre : public BossMobs {
    private:
        void updateBasicAttributes() override;
    public:
        // ctor dtor
        Ogre(int level, int expReward, Mobloot& mobLoots);
        ~Ogre();


};

#endif