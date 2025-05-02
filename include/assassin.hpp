#ifndef ASSASSIN_HPP
#define ASSASSIN_HPP

#include "character.hpp"
#include <string>
using namespace std;

class Assassin : public Character {
    private:
        float criticalChance;
        int criticalMultiplier;
        void updateBasicAttributes() override;
    public:
        // ctor dtor
        Assassin(string name,  int strength = 16, int agility = 26, int intelligence = 20, int level = BASE_LEVEL, int exp = BASE_EXP, int gold = BASE_GOLD, int masteryCost = BASE_MASTERY_COST);
        ~Assassin();

        // setter getter
        float getCriticalChance() const;
        int getCriticalMultiplier() const;
        void setCriticalChance(float criticalChance);
        void setCriticalMultiplier(int criticalMultiplier);

        // Fungsi override
        void attack(Unit& target, Inventory& inventory) override;
        void takeDamage(int damage) override;
        void levelUp() override;
};

#endif