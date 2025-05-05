#include "../include/fighter.hpp"
#include <iostream>
using namespace std;

Fighter::Fighter(string name, int strength, int agility, int intelligence, int level, int exp, int gold, int masteryCost, vector<string> skillNames)
: Character(name, strength, agility, intelligence, level, exp, gold, masteryCost, skillNames, "Fighter") {
    updateBasicAttributes();
    for (int i = 0; i < skillTree.currentSkills.size(); i++) {
        addSkill(skillTree.currentSkills[i]->getSkill());
    }
}

Fighter::~Fighter() {}

float Fighter::getBlockChance() const { return blockChance;}
void Fighter::setBlockChance(float blockChance) { this->blockChance = blockChance;}

void Fighter::takeDamage(int damage, Inventory& inventory) {
    if ((rand() % 100 + 1)< blockChance) { // Peluang diblok
        cout << "Serangan musuh berhasil diblok" << endl;
        return;
    } 
    Unit::takeDamage(damage, inventory); 
}

void Fighter::useSkill(Skill* skill, Unit& target, Inventory& inventory) {
    Unit::useSkill(skill, target, inventory);
    currentHealth += stats.getStrength() * 0.25;
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
}

void Fighter::updateBasicAttributes() {
    setAttackDamage(15 + 5 * getStats().getStrength() + 2 *getStats().getAgility());
    setBlockChance(getStats().getAgility() / 1.4); 
}

void Fighter::levelUp() {
    setMasteryCost(getMasteryCost() + 5);
    setExp(0);
    stats.setStrength(stats.getStrength() + 3);
    stats.setAgility(stats.getAgility() + 2);
    stats.setIntelligence(stats.getIntelligence() + 1);
    Unit::updateBasicAttributes(); 
    updateBasicAttributes();
    for (Skill* skill : skills) {
        skill->setDamage(skill->getDamage() + 20);
        skill->setManaCost(skill->getManaCost() + 10);
    }
    Character::reset();
}





