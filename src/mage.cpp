#include "../include/mage.hpp"
#include <iostream>
using namespace std;

Mage::Mage(string name, int strength, int agility, int intelligence, int level, int exp, int gold, int masteryCost)
 : Character(name, strength, agility, intelligence, level, exp, gold, masteryCost, "Mage") {
    updateBasicAttributes();
    for (int i = 0; i < skillTree.currentSkills.size(); i++) {
        addSkill(skillTree.currentSkills[i]->getSkill());
    }
}

Mage::~Mage() {}

int Mage::getExtraMana() const { return extraMana;}
void Mage::setExtraMana(int extraMana) { this->extraMana = extraMana;}

void Mage::attack(Unit& target, Inventory& inventory) {
    Unit::attack(target, inventory);
    Unit::restoreMana(extraMana);
}

void Mage::useSkill(Skill* skill, Unit& target) {
    skill->setDamage(skill->getDamage() + stats.getIntelligence() * 0.5);
    Unit::useSkill(skill, target); 
    currentMana -= stats.getIntelligence();
    if (currentMana < 0) {
        currentMana = 0;
    }
}

void Mage::updateBasicAttributes() {
    setAttackDamage(8 + 10*getStats().getIntelligence()); 
    setExtraMana(getStats().getIntelligence() / 3);
}

void Mage::levelUp() {
    setMasteryCost(getMasteryCost() + 5);
    setExp(0);
    stats.setStrength(stats.getStrength() * 1.2);
    stats.setAgility(stats.getAgility() * 1.5);
    stats.setIntelligence(stats.getIntelligence() * 2);
    Unit::updateBasicAttributes(); 
    updateBasicAttributes();
    Character::reset();
}





