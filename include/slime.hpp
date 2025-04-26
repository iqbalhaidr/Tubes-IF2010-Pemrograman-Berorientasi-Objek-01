#ifndef SLIME_HPP
#define SLIME_HPP

#include "Mobs.hpp"
#include <string>
using namespace std;

class Slime : public Mobs {
    private:
        bool acidicCorrosion;
        // Mastery mastery;
        // Effect activeEffect;
    public:
        // ctor dtor
        Slime(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int healValue);
        ~Slime();

        // setter getter
        void setAcidicCorrosion(Unit& target);


};

#endif