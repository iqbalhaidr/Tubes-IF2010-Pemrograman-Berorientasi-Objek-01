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
        Fighter(string name);
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