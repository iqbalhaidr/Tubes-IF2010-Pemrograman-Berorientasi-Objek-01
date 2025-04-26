#ifndef SKELETON_HPP
#define SKELETON_HPP

#include "basicMobs.hpp"
#include <string>
using namespace std;

class Skeleton : public BasicMobs {
    public:
        // ctor dtor
        Skeleton(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots);
        ~Skeleton();



};

#endif