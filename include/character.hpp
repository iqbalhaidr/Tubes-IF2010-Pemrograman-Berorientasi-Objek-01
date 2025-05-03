#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#define BASE_LEVEL 1
#define BASE_EXP 0
#define BASE_GOLD 0
#define BASE_MASTERY_COST 5

#include "unit.hpp"
#include "skillTree.hpp"

#include <algorithm>
#include <string>

using namespace std;

class Character : public Unit {
    protected:
        int exp;
        int gold;
        int masteryCost;
        string type;
        SkillTree skillTree;
        void loadCharacterSkills(vector<string> skillNames);
    public:
        // ctor dtor
        Character(string name, int strength, int agility, int intelligence, int level, int exp, int gold, int masteryCost, vector<string> skillNames, string type);
        virtual ~Character();

        // setter getter
        int getExp() const;
        int getGold() const;
        int getMasteryCost() const;
        SkillTree getSkillTree() const;
        string getType() const;
        void setLevel(int level);
        void setExp(int exp);
        void setGold(int gold);
        void setMasteryCost(int masteryCost);
        void setType(string type);
        void displayAvailableSkillUpgrades();
        void UpgradeSkill(string& name);
        void displayCharacter();

        // Fungsi
        virtual void levelUp() = 0;

        // Fungsi override Unit
        void reset();



};

#endif