#include "fighter.hpp"
#include <iostream>
using namespace std;

Fighter::Fighter(string name)
: Character(name, 26, 17, 13, 1, 0, 0, 5, "Fighter") {
    updateBasicAttributes();
}

Fighter::~Fighter() {}

float Fighter::getBlockChance() const { return blockChance;}
void Fighter::setBlockChance(float blockChance) { this->blockChance = blockChance;}

void Fighter::takeDamage(int damage) {
    if (rand() % 100 < blockChance) { // Peluang diblok
        cout << "Serangan musuh berhasil diblok" << endl;
        return;
    } 
    Unit::takeDamage(damage); 
}

void Fighter::useSkill(Skill* skill, Unit& target) {
    Unit::useSkill(skill, target);
    currentHealth += stats.getStrength() * 0.25;
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
}

void Fighter::updateBasicAttributes() {
    setAttackDamage(15 + 4 * getStats().getStrength() + 2 *getStats().getAgility());
    setBlockChance(getStats().getAgility() * 2 / 100); 
}

void Fighter::levelUp() {
    setMasteryCost(getMasteryCost() + 5);
    setExp(0);
    stats.setStrength(stats.getStrength() * 2);
    stats.setAgility(stats.getAgility() * 1.5);
    stats.setIntelligence(stats.getIntelligence() * 1.2);
    Unit::updateBasicAttributes(); 
    updateBasicAttributes();
    Character::reset();
}





