#include "../include/berserker.hpp"
#include <iostream>
using namespace std;

Berserker::Berserker(string name, int strength, int agility, int intelligence, int level, int exp, int gold, int masteryCost, vector<string> skillNames)
: Character(name , strength, agility, intelligence, level, exp, gold, masteryCost, skillNames, "Berserker") {
    updateBasicAttributes();
    for (int i = 0; i < skillTree.currentSkills.size(); i++) {
        addSkill(skillTree.currentSkills[i]->getSkill());
    }
}

Berserker::~Berserker() {}

int Berserker::getRageMultiplier() const { return rageMultiplier;}
void Berserker::setRageMultiplier(int rageMultiplier) { this->rageMultiplier = rageMultiplier;}

void Berserker::attack(Unit& target, Inventory& inventory)  {
    int totalDamage = calculateDamage(target, attackDamage, inventory); 
    totalDamage *= rageMultiplier; 
    target.takeDamage(totalDamage, inventory); 
}

void Berserker::useSkill(Skill* skill, Unit& target, Inventory& inventory) {
    Unit::useSkill(skill, target, inventory); 
    rageMultiplier += 3;
}

void Berserker::updateBasicAttributes() {
    setAttackDamage(20 + 8 * getStats().getStrength());
    setRageMultiplier(getStats().getStrength() / 4);
}

void Berserker::levelUp() {
    setMasteryCost(getMasteryCost() + 5);
    setExp(0);
    stats.setStrength(stats.getStrength() + 4);
    stats.setAgility(stats.getAgility() * + 1);
    stats.setIntelligence(stats.getIntelligence() + 1);
    Unit::updateBasicAttributes(); 
    updateBasicAttributes();
    for (Skill* skill : skills) {
        skill->setDamage(skill->getDamage() + 20);
        skill->setManaCost(skill->getManaCost() + 10);
    }
    Character::reset();
}

