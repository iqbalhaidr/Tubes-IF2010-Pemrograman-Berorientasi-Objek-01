#ifndef MAGE_HPP
#define MAGE_HPP

#include "character.hpp"
#include <string>
using namespace std;

class Mage : public Character {
    private:
        int extraMana;
    public:
        // ctor dtor
        Mage(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int level, int exp, int gold, int extraMana);
        ~Mage();

        // setter getter
        int getExtraMana() const;
        void setExtraMana(int extraMana);

        // Fungsi
        void attack(Unit& target);
        void useSkill(string& skill, Unit& target);
        void levelUp();
};

#endif