#ifndef FIGHTER_HPP
#define FIGHTER_HPP

#include "character.hpp"
#include <string>
using namespace std;

class Fighter : public Character {
    private:
        float blockChance;
        void updateBasicAttributes() override;
    public:
        // ctor dtor
        Fighter(string name, int strength = 126, int agility = 17, int intelligence = 13, int level = BASE_LEVEL, int exp = BASE_EXP, int gold = BASE_GOLD, int masteryCost = BASE_MASTERY_COST);
        ~Fighter();

        // setter getter
        float getBlockChance() const;
        void setBlockChance(float blockChance);

        // Fungsi
        void takeDamage(int damage);
        void useSkill(Skill* skill, Unit& target);
        void levelUp();
};

#endif