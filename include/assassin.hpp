#ifndef ASSASSIN_HPP
#define ASSASSIN_HPP

#include "character.hpp"
#include <string>
using namespace std;

class Assassin : public Character {
    private:
        float criticalChance;
        int criticalMultiplier;
    public:
        // ctor dtor
        Assassin(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage, int strength, int agility, int intelligence, int level, int exp, int gold, float criticalChance, int criticalMultiplier);
        ~Assassin();

        // setter getter
        float getCriticalChance() const;
        int getCriticalMultiplier() const;
        void setCriticalChance(float criticalChance);
        void setCriticalMultiplier(int criticalMultiplier);

        // Fungsi override
        void attack(Unit& target) override;
        void takeDamage(int damage) override;
        void levelUp() override;
};

#endif