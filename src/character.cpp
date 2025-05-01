#include "../include/character.hpp"
#include <iostream>
using namespace std;

Character::Character(string name, int strength, int agility, int intelligence, int level, int exp, int gold, int masteryCost, string type)
: Unit(name, strength, agility, intelligence, level), skillTree(type){
    setExp(exp);
    setGold(gold);
    setMasteryCost(masteryCost);
    setType(type);
}

Character::~Character() {}

int Character::getExp() const { return exp;}
int Character::getGold() const { return gold;}
int Character::getMasteryCost() const { return masteryCost;}
string Character::getType() const { return type;}
SkillTree Character::getSkillTree() const { return skillTree;}

void Character::setLevel(int level) { this->level = level;}
void Character::setExp(int exp) { this->exp = exp;}
void Character::setGold(int gold) { this->gold = gold;}
void Character::setMasteryCost(int masteryCost) { this->masteryCost = masteryCost;}
void Character::setType(string type) { this->type = type;}
void Character::displayAvailableSkillUpgrades() {}
void Character::UpgradeSkill(vector<string> skills) {}

void Character::reset() {
    currentHealth = maxHealth;
    currentMana = maxMana;
    activeEffects.clear(); 
}
