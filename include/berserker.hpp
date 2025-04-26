#ifndef BERSERKER_HPP
#define BERSERKER_HPP

#include "character.hpp"
#include <string>
using namespace std;

class Berserker : public Character {
    private:
        int rageMultiplier;
    public:
        // ctor dtor
        Berserker(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int level, int exp, int gold, int rageMultiplier);
        ~Berserker();

        // setter getter
        int getRageMultiplier() const;
        void setRageMultiplier(int rageMultiplier);

        // Fungsi override
        void attack(Unit& target) ;
        void takeDamage(int damage);
        void useSkill(string& skill, Unit& target);
        void levelUp();
};

#endif