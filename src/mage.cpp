#include "mage.hpp"
#include <iostream>
using namespace std;

Mage::Mage(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage, int strength, int agility, int intelligence, int level, int exp, int gold, int extraMana)
 : Character(name, maxHealth, healthRegen, maxMana, manaRegen, attackDamage, strength, agility, intelligence, level, exp, gold, "Mage") {
    this->extraMana = extraMana;

}

Mage::~Mage() {}

int Mage::getExtraMana() const { return extraMana;}
void Mage::setExtraMana(int extraMana) { this->extraMana = extraMana;}

void Mage::attack(Unit& target) {
    // attackDamage fungsi iqbal
    // target.takeDamage(totalAttackDamage);
    Unit::restoreMana(extraMana);
}

void Mage::useSkill(Unit& target) {
    Unit::useSkill(target); 
    currentMana -= stats.getIntelligence();
    // attackDamage fungsi iqbal
    totalAttackDamage += stats.getIntelligence();
    if (currentMana < 0) {
        currentMana = 0;
    }
}

void Mage::levelUp() {
    masteryCost += 5; 
    stats.setStrength(stats.getStrength() * 1.2);
    stats.setAgility(stats.getAgility() * 1.5);
    stats.setIntelligence(stats.getIntelligence() * 2);
}





