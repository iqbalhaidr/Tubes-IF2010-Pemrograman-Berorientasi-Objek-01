#ifndef FIGHTER_HPP
#define FIGHTER_HPP

#include "character.hpp"
#include <string>
using namespace std;

class Fighter : public Character {
    private:
        float blockChance;
    public:
        // ctor dtor
        Fighter(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int level, int exp, int gold, float blockChance);
        ~Fighter();

        // setter getter
        float getBlockChance() const;
        void setBlockChance(float blockChance);

        // Fungsi
        void takeDamage(int damage);
        void useSkill(string& skill, Unit& target);
        void levelUp();
};

#endif