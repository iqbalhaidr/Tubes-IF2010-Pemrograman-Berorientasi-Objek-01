#ifndef MAGE_HPP
#define MAGE_HPP

#include "character.hpp"
#include <string>
using namespace std;

class Mage : public Character {
    private:
        int extraMana;
        void updateBasicAttributes() override;
    public:
        // ctor dtor
        Mage(string name, int strength = 16, int agility = 20, int intelligence = 25, int level = BASE_LEVEL, int exp = BASE_EXP, int gold = BASE_GOLD, int masteryCost = BASE_MASTERY_COST, vector<string> skillNames = {});
        ~Mage();

        // setter getter
        int getExtraMana() const;
        void setExtraMana(int extraMana);

        // Fungsi
        void attack(Unit& target, Inventory& inventory) override;
        void useSkill(Skill* skill, Unit& target, Inventory& inventory);
        void levelUp();
};

#endif