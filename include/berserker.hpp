#ifndef BERSERKER_HPP
#define BERSERKER_HPP

#include "character.hpp"
#include <string>
using namespace std;

class Berserker : public Character {
    private:
        int rageMultiplier;
        void updateBasicAttributes() override;
    public:
        // ctor dtor
        Berserker(string name);
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