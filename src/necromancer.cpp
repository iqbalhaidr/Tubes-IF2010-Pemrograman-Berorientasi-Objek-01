#include "../include/necromancer.hpp"

Necromancer::Necromancer(string name, int strength, int agility, int intelligence, int level, int exp, int gold, int masteryCost, vector<string> skillNames)
: Character(name, strength, agility, intelligence, level, exp, gold, masteryCost, skillNames, "Necromancer") {
    updateBasicAttributes();
    for (int i = 0; i < skillTree.currentSkills.size(); i++) {
        addSkill(skillTree.currentSkills[i]->getSkill());
    }
    this->summonTurns = 0; 
    this->summons = false;
}

Necromancer::~Necromancer() {
}

double Necromancer::getSummonChance() const { return summonChance;}
void Necromancer::setSummonChance(double summonChance) { this->summonChance = summonChance;}

void Necromancer::attack(Unit& target, Inventory& inventory) {
    if (!summons && (rand() % 100 + 1) < summonChance) {
        summons = true;
        summonTurns = 4;
        Unit::attack(target, inventory); 
    }
    if (summons) {
        summonTurns--;
        if (summonTurns == 0) {
            summons = false;
        }
        int totalDamage = calculateDamage(target, attackDamage, inventory); 
        totalDamage += stats.getIntelligence() * 0.25; 
        target.takeDamage(totalDamage, inventory); // damage dari minion
    }
}

void Necromancer::useSkill(Skill* skill, Unit& target, Inventory& inventory) {
    Unit::useSkill(skill, target, inventory); 
    target.takeDamage(getStats().getIntelligence() * 0.25, inventory);
    currentHealth += getStats().getIntelligence() * 0.25;
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
}

void Necromancer::updateBasicAttributes() {
    setAttackDamage(12 + 9*getStats().getIntelligence() + 1*getStats().getStrength());
    setSummonChance(getStats().getIntelligence() / 1.8);
}

// Mekanisme ketika char level up
void Necromancer::levelUp() {
    setMasteryCost(getMasteryCost() + 5);
    setExp(0);
    stats.setStrength(stats.getStrength() + 1);
    stats.setAgility(stats.getAgility() + 1);
    stats.setIntelligence(stats.getIntelligence() + 4);
    Unit::updateBasicAttributes(); 
    updateBasicAttributes();
    for (Skill* skill : skills) {
        skill->setDamage(skill->getDamage() + 20);
        skill->setManaCost(skill->getManaCost() + 10);
    }
    Character::reset();

}


