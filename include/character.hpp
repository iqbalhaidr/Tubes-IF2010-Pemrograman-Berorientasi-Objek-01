#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "unit.hpp"
#include <algorithm>
#include <string>
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
        Character(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int level, int exp, int gold, string type);
        ~Character();

        // setter getter
        int getLevel() const;
        int getExp() const;
        string getMastery() const; //TEMPORARY
        int getGold() const;
        int getMasteryCost() const;
        void setLevel(int level);
        void setExp(int exp);
        void setMastery(string mastery); //TEMPORARY
        void setGold(int gold);
        void setMasteryCost(int masteryCost);

        // Fungsi
        virtual void levelUp() = 0;

        // Fungsi override Unit
        void reset() override;



};

#endif