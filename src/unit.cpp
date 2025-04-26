#include "unit.hpp"
#include <iostream>
#include <string>
using namespace std;

Unit::Unit(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage, int strength, int agility, int intelligence) : stats(strength, agility, intelligence) {
    this->name = name;
    this->maxHealth = maxHealth;
    this->currentHealth = maxHealth;
    this->healthRegen = healthRegen;
    this->maxMana = maxMana;
    this->currentMana = maxMana;
    this->manaRegen = manaRegen;
    this->attackDamage = attackDamage;
    this->isStun = false; 
}

Unit::~Unit() {}

string Unit::getName() const { return name;}
int Unit::getCurrentHealth() const { return currentHealth;}
int Unit::getMaxHealth() const { return maxHealth;}
int Unit::getHealthRegen() const { return healthRegen;}
int Unit::getCurrentMana() const { return currentMana;}
int Unit::getMaxMana() const { return maxMana;}
int Unit::getManaRegen() const { return manaRegen;}
int Unit::getAttackDamage() const { return attackDamage;}
Stats Unit::getStats() const { return stats;}
vector<string> Unit::getSkills() const { return skills;} // TEMPORARY
vector<string> Unit::getEffects() const { return effects;} // TEMPORARY

void Unit::setName(string name) { this->name = name;}
void Unit::setCurrentHealth(int currentHealth) { this->currentHealth = currentHealth;}
void Unit::setMaxHealth(int maxHealth) { this->maxHealth = maxHealth;}
void Unit::setHealthRegen(int healthRegen) { this->healthRegen = healthRegen;}
void Unit::setCurrentMana(int currentMana) { this->currentMana = currentMana;}
void Unit::setMaxMana(int maxMana) { this->maxMana = maxMana;}
void Unit::setManaRegen(int manaRegen) { this->manaRegen = manaRegen;}
void Unit::setAttackDamage(int attackDamage) { this->attackDamage = attackDamage;}
void Unit::setStats(int strength, int agility, int intelligence) {
    stats.setStrength(strength);
    stats.setAgility(agility);
    stats.setIntelligence(intelligence);
}

void Unit::attack(Unit& target) {
    //ambil attackdamage dari class damage
    target.takeDamage(attackDamage);
}

void Unit::takeDamage(int damage) {
    currentHealth -= damage;
    if (currentHealth < 0) {
        currentHealth = 0;
    }
}

void Unit::heal(int amount) {
    currentHealth += amount;
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
}

void Unit::restoreMana(int amount) {
    currentMana += amount;
    if (currentMana > maxMana) {
        currentMana = maxMana;
    }
}

void Unit::useSkill(string skill) {
    // logika penggunaan skill
    // 1. cek mana cukup untuk useskill
    // 2. kurangi mana
    // 3. attack proses damage
    // 4. apply efek
}

void Unit::addSkill(string skill) {
    skills.push_back(skill); // TEMPORARY
}
void Unit::removeSkill(string skill) {
    auto it = find(skills.begin(), skills.end(), skill);
    if (it != skills.end()) {
        skills.erase(it); // TEMPORARY
    }
}

void Unit::addEffect(string effect) {
    effects.push_back(effect); // TEMPORARY
}

void Unit::removeEffect(string effect) {
    auto it = find(effects.begin(), effects.end(), effect);
    if (it != effects.end()) {
        effects.erase(it); // TEMPORARY
    }
}
