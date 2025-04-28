#ifndef CHARACTER_HPP
#define CHARACTER_HPP


#include "unit.hpp"
#include <algorithm>
#include <string>

#define BASE_LEVEL 1
#define BASE_EXP 0
#define BASE_GOLD 0
#define BASE_MASTERY_COST 0
using namespace std;

class Character : public Unit {
    protected:
        int level;
        int exp;
        int gold;
        int masteryCost;
        string type;
    public:
        // ctor dtor
        Character(string name, int strength, int agility, int intelligence, int level = BASE_LEVEL, int exp = BASE_EXP, int gold = BASE_GOLD, int masteryCost = BASE_MASTERY_COST, string type);
        ~Character();

        // setter getter
        int getLevel() const;
        int getExp() const;
        int getGold() const;
        int getMasteryCost() const;
        string getType() const;
        void setLevel(int level);
        void setExp(int exp);
        void setGold(int gold);
        void setMasteryCost(int masteryCost);
        void setType(string type);

        // Fungsi
        virtual void levelUp() = 0;

        // Fungsi override Unit
        void reset() override;



};

#endif