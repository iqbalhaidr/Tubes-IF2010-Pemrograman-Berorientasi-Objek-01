#include "../include/assassin.hpp"
#include <iostream>
using namespace std;

Assassin::Assassin(string name, int strength, int agility, int intelligence, int level, int exp, int gold, int masteryCost, vector<string> skillNames)
 : Character(name, strength, agility, intelligence, level, exp, gold, masteryCost, skillNames, "Assassin") {
    updateBasicAttributes(); // kecuali critmultiplier
    for (int i = 0; i < skillTree.currentSkills.size(); i++) {
        addSkill(skillTree.currentSkills[i]->getSkill());
    }
    cout << "yes\n";
}

Assassin::~Assassin() {}

float Assassin::getCriticalChance() const { return criticalChance;}
int Assassin::getCriticalMultiplier() const { return criticalMultiplier;}

void Assassin::setCriticalChance(float criticalChance) { this->criticalChance = criticalChance;}
void Assassin::setCriticalMultiplier(int criticalMultiplier) { this->criticalMultiplier = criticalMultiplier;}

void Assassin::attack(Unit& target, Inventory& inventory) {
    if ((rand() % 100 + 1)< criticalChance) { 
        int totalDamage = calculateDamage(target, attackDamage, inventory); 
        totalDamage *= criticalMultiplier; 
        cout << "Critical hit!" << endl;
        target.takeDamage(totalDamage, inventory);
    } else {
        Unit::attack(target, inventory); 
    }

}

void Assassin::takeDamage(int damage, Inventory& inventory) {
    if ((rand() % 100 + 1) < stats.getAgility()) { 
        cout << "Serangan terhindar" << endl;
        return; // No damage taken
    }
    Unit::takeDamage(damage, inventory);
}

void Assassin::updateBasicAttributes() {
    setAttackDamage(12 + 7 * getStats().getAgility() + getStats().getStrength());
    setCriticalMultiplier(getStats().getAgility() / 5);
    setCriticalChance(getStats().getAgility() * 4 / 100);
}
void Assassin::levelUp() {
    setMasteryCost(getMasteryCost() + 5);
    setExp(0);
    stats.setStrength(stats.getStrength() * 1.2);
    stats.setAgility(stats.getAgility() * 1.5);
    stats.setIntelligence(stats.getIntelligence() * 1.3);
    Unit::updateBasicAttributes(); 
    updateBasicAttributes();
    Character::reset();
}

