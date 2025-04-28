#ifndef SKELETON_HPP
#define SKELETON_HPP

#include "basicMobs.hpp"
#include <string>
using namespace std;

class Skeleton : public BasicMobs {
    public:
        // ctor dtor
        Skeleton(int level, int expReward, Mobloot& mobLoots);
        ~Skeleton();
        void updateBasicAttributes() override ;



};

#endif