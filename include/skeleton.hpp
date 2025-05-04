#ifndef SKELETON_HPP
#define SKELETON_HPP

#include "basicMobs.hpp"
#include <string>
using namespace std;

class Skeleton : public BasicMobs {
    private:
        void updateBasicAttributes() override;
    public:
        // ctor dtor
        Skeleton(int level, int expReward, Mobloot& mobLoots);
        ~Skeleton();



};

#endif