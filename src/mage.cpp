#include "../include/mage.hpp"
#include <iostream>
using namespace std;

Mage::Mage(string name, int strength, int agility, int intelligence, int level, int exp, int gold, int masteryCost, vector<string> skillNames)
 : Character(name, strength, agility, intelligence, level, exp, gold, masteryCost, skillNames, "Mage") {
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

void Mage::useSkill(Skill* skill, Unit& target, Inventory& inventory) {
    skill->setDamage(skill->getDamage() + stats.getIntelligence() * 0.5);
    Unit::useSkill(skill, target, inventory); 
    currentMana -= stats.getIntelligence();
    if (currentMana < 0) {
        currentMana = 0;
    }
    skill->setDamage(skill->getDamage() - stats.getIntelligence() * 0.5);
}

void Mage::updateBasicAttributes() {
    setAttackDamage(8 + 6*getStats().getIntelligence() + 2*getStats().getAgility()); 
    setExtraMana(getStats().getIntelligence() / 7);
}

void Mage::levelUp() {
    setMasteryCost(getMasteryCost() + 5);
    setExp(0);
    stats.setStrength(stats.getStrength() + 1);
    stats.setAgility(stats.getAgility() + 2);
    stats.setIntelligence(stats.getIntelligence() + 3);
    Unit::updateBasicAttributes(); 
    updateBasicAttributes();
    for (Skill* skill : skills) {
        skill->setDamage(skill->getDamage() + 20);
        skill->setManaCost(skill->getManaCost() + 10);
    }
    Character::reset();
}





