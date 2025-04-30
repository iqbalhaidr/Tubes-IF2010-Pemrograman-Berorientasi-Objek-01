#ifndef CHARACTER_HPP
#define CHARACTER_HPP


#include "unit.hpp"
#include <algorithm>
#include <string>

using namespace std;

class Character : public Unit {
    protected:
        int exp;
        int gold;
        int masteryCost;
        string type;
    public:
        // ctor dtor
        Character(string name, int strength, int agility, int intelligence, int level, int exp, int gold, int masteryCost, string type);
        ~Character();

        // setter getter
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
        void reset();



};

#endif