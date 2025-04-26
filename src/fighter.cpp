#include "fighter.hpp"
#include <iostream>
using namespace std;

Fighter::Fighter(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage, int strength, int agility, int intelligence, int level, int exp, int gold, float blockChance) 
: Character(name, maxHealth, healthRegen, maxMana, manaRegen, attackDamage, strength, agility, intelligence, level, exp, gold, "Fighter") {
    this->blockChance = blockChance;
}

Fighter::~Fighter() {}

float Fighter::getBlockChance() const { return blockChance;}
void Fighter::setBlockChance(float blockChance) { this->blockChance = blockChance;}

void Fighter::takeDamage(int damage) {
    if (rand() % 100 < blockChance) { // Peluang diblok
        cout << "Serangan musuh berhasil diblok" << endl;
        return;
    } 

    currentHealth -= damage;
    if (currentHealth < 0) {
        currentHealth = 0;
    }
}

// void Fighter::useSkill() {
    // currentHealth += stats.getStrength() * 0.5;
    // if (currentHealth > maxHealth) {
        // currentHealth = maxHealth;
    // }
// }

void Fighter::levelUp() {
    masteryCost += 5; 
    stats.setStrength(stats.getStrength() * 2);
    stats.setAgility(stats.getAgility() * 1.5);
    stats.setIntelligence(stats.getIntelligence() * 1.2);
}




