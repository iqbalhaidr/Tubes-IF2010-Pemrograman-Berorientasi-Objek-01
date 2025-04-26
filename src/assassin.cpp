#include "assassin.hpp"
#include <iostream>
using namespace std;

Assassin::Assassin(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage, int strength, int agility, int intelligence, int level, int exp, int gold, float criticalChance, int criticalMultiplier)
 : Character(name, maxHealth, healthRegen, maxMana, manaRegen, attackDamage, strength, agility, intelligence, level, exp, gold, "Assassin") {
    this->criticalChance = criticalChance;
    this->criticalMultiplier = criticalMultiplier; 
}

Assassin::~Assassin() {}

float Assassin::getCriticalChance() const { return criticalChance;}
int Assassin::getCriticalMultiplier() const { return criticalMultiplier;}

void Assassin::setCriticalChance(float criticalChance) { this->criticalChance = criticalChance;}
void Assassin::setCriticalMultiplier(int criticalMultiplier) { this->criticalMultiplier = criticalMultiplier;}

void Assassin::attack(Unit& target) {
    if (rand() % 100 < criticalChance) { 
        // panggil fungsi damage dengan paramter criticalmultiplier
    } else {
        // panggil fungsi damage biasa
    }
    // target.takeDamage(damage);
}

void Assassin::takeDamage(int damage) {
    if (rand() % 100 < stats.getAgility() / 100) { 
        cout << "Serangan terhindar" << endl;
        return; // No damage taken
    }

    currentHealth -= damage;
    if (currentHealth < 0) {
        currentHealth = 0;
    }
}
void Assassin::levelUp() {
    masteryCost += 5; 
    stats.setStrength(stats.getStrength() * 1.2);
    stats.setAgility(stats.getAgility() * 2);
    stats.setIntelligence(stats.getIntelligence() * 1.5);
}