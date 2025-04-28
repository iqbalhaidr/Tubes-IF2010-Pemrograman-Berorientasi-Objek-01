#include "berserker.hpp"
#include <iostream>
using namespace std;

Berserker::Berserker(string name, int strength, int agility, int intelligence, int level, int exp, int gold, int masteryCost, string type, int rageMultiplier)
: Character(name ,strength, agility, intelligence, level, exp, gold, masteryCost, "Berserker") {
    updateBasicAttributes();
    setRageMultiplier(rageMultiplier);
}

Berserker::~Berserker() {}

int Berserker::getRageMultiplier() const { return rageMultiplier;}
void Berserker::setRageMultiplier(int rageMultiplier) { this->rageMultiplier = rageMultiplier;}

void Berserker::attack(Unit& target, Inventory& inventory)  {
    int totalDamage = calculateDamage(target, attackDamage, inventory); 
    totalDamage *= rageMultiplier; 
    target.takeDamage(totalDamage); 
}

void Berserker::useSkill(Skill* skill, Unit& target) {
    Unit::useSkill(skill, target); 
    rageMultiplier += 3;
}

void Berserker::updateBasicAttributes() {
    setAttackDamage(20 + 8 * getStats().getStrength());
}

void Berserker::levelUp() {
    setMasteryCost(getMasteryCost() + 5);
    setExp(0);
    stats.setStrength(stats.getStrength() * 2.5);
    stats.setAgility(stats.getAgility() * 1.2);
    stats.setIntelligence(stats.getIntelligence() * 1.2);
    Unit::updateBasicAttributes(); 
    updateBasicAttributes();
    Character::reset();
}

