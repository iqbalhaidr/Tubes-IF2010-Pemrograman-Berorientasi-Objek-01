#include "character.hpp"
#include <iostream>
using namespace std;

Character::Character(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage, int strength, int agility, int intelligence, int level, int exp, int gold, string type) 
: Unit(name, maxHealth, healthRegen, maxMana, manaRegen, attackDamage, strength, agility, intelligence) {
    this->level = level;
    this->exp = exp;
    this->gold = gold;
    this->masteryCost = 0; 
    this->type = type;
}

Character::~Character() {}

int Character::getLevel() const { return level;}
int Character::getExp() const { return exp;}
int Character::getGold() const { return gold;}
int Character::getMasteryCost() const { return masteryCost;}

void Character::setLevel(int level) { this->level = level;}
void Character::setExp(int exp) { this->exp = exp;}
void Character::setGold(int gold) { this->gold = gold;}
void Character::setMasteryCost(int masteryCost) { this->masteryCost = masteryCost;}

void Character::reset() {
    currentHealth = maxHealth;
    currentMana = maxMana;
}
