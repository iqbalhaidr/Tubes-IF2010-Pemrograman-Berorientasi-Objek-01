#ifndef BERSERKER_HPP
#define BERSERKER_HPP

#include "character.hpp"
#include <string>
using namespace std;

// Character(string name, int strength, int agility, int intelligence, int level, int exp, int gold, int masteryCost, string type);

class Berserker : public Character {
    private:
        int rageMultiplier;
        void updateBasicAttributes() override;
    public:
        // ctor dtor
        Berserker(string name, int strength = 28, int agility = 17, int intelligence = 1, int level = BASE_LEVEL, int exp = BASE_EXP, int gold = BASE_GOLD, int masteryCost = BASE_MASTERY_COST);
        ~Berserker();

        // setter getter
        int getRageMultiplier() const;
        void setRageMultiplier(int rageMultiplier);

        // Fungsi override
        void attack(Unit& target, Inventory& inventory);
        void takeDamage(int damage);
        void useSkill(Skill* skill, Unit& target);
        void levelUp();
};

#endif