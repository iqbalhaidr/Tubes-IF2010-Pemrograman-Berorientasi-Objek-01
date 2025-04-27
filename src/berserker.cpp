#include "berserker.hpp"
#include <iostream>
using namespace std;

Berserker::Berserker(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage, int strength, int agility, int intelligence, int level, int exp, int gold, int rageMultiplier) 
: Character(name, maxHealth, healthRegen, maxMana, manaRegen, attackDamage, strength, agility, intelligence, level, exp, gold, "Berserker") {
    this->rageMultiplier = rageMultiplier; // Set default rage multiplier
}

Berserker::~Berserker() {}

int Berserker::getRageMultiplier() const { return rageMultiplier;}
void Berserker::setRageMultiplier(int rageMultiplier) { this->rageMultiplier = rageMultiplier;}

void Berserker::attack(Unit& target)  {
    //int damage = attackDamage * rageMultiplier; // belom
}

void Berserker::useSkill(string& skill, Unit& target) {
    Unit::useSkill(skill, target); // Call the base class method
    rageMultiplier += 1;
}

void Berserker::levelUp() {
    masteryCost += 5; 
    stats.setStrength(stats.getStrength() * 2.5);
    stats.setAgility(stats.getAgility() * 1.2);
    stats.setIntelligence(stats.getIntelligence() * 1.2);
}

