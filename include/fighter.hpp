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
        Fighter(string name, int strength = 26, int agility = 17, int intelligence = 13, int level = BASE_LEVEL, int exp = BASE_EXP, int gold = BASE_GOLD, int masteryCost = BASE_MASTERY_COST, vector<string> skillNames = {});
        ~Fighter();

        // setter getter
        float getBlockChance() const;
        void setBlockChance(float blockChance);

        // Fungsi
        void takeDamage(int damage, Inventory& inventory);
        void useSkill(Skill* skill, Unit& target, Inventory& inventory);
        void levelUp();
};

#endif