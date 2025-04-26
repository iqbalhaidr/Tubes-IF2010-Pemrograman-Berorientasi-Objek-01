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
    public:
        // ctor dtor
        Necromancer(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence,  int level, int exp, string mastery, int gold, double summonChance);
        ~Necromancer();

        // setter getter
        double getSummonChance() const;
        void setSummonChance(double criticalChance);

        // Fungsi
        void attack(Unit& target);
        // void useSkill(Unit& target);
        void levelUp();
};

#endif