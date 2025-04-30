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
        Mage(string name);
        ~Mage();

        // setter getter
        int getExtraMana() const;
        void setExtraMana(int extraMana);

        // Fungsi
        void attack(Unit& target, Inventory& inventory) override;
        void useSkill(Skill* skill, Unit& target);
        void levelUp();
};

#endif