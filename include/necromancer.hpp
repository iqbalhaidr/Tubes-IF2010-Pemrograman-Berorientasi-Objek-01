#ifndef NECROMANCER_HPP
#define NECROMANCER_HPP

#include "character.hpp"

#include <string>
#include <vector>
using namespace std;

class Necromancer : public Character {
    private:
        bool summons; 
        double summonChance; 
        int summonTurns;
        void updateBasicAttributes() override;
    public:
        // ctor dtor
        Necromancer(string name, int strength = 13, int agility = 16, int intelligence = 28, int level = BASE_LEVEL, int exp = BASE_EXP, int gold = BASE_GOLD, int masteryCost = BASE_MASTERY_COST, vector<string> skillNames = {});
        ~Necromancer();

        // setter getter
        double getSummonChance() const;

        void setSummonChance(double criticalChance);

        // Fungsi
        void attack(Unit& target, Inventory& inventory) ;
        void useSkill(Skill* skill, Unit& target, Inventory& inventory);
        void levelUp();
};

#endif