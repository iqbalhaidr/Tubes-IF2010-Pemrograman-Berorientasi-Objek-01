#include "../include/necromancer.hpp"

Necromancer::Necromancer(string name, int strength, int agility, int intelligence, int level, int exp, int gold, int masteryCost)
: Character(name, strength, agility, intelligence, level, exp, gold, masteryCost, "Necromancer") {
    updateBasicAttributes();
    this->summonTurns = 0; 
    this->summons = false;
}

Necromancer::~Necromancer() {
}

double Necromancer::getSummonChance() const { return summonChance;}
void Necromancer::setSummonChance(double summonChance) { this->summonChance = summonChance;}

void Necromancer::attack(Unit& target, Inventory& inventory) {
    if (!summons && (rand() + 1 % 100 + 1) < summonChance) {
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
        target.takeDamage(totalDamage); // damage dari minion
    }
}

void Necromancer::useSkill(Skill* skill, Unit& target) {
    Unit::useSkill(skill, target); 
    target.takeDamage(getStats().getIntelligence() * 0.25);
    currentHealth += getStats().getIntelligence() * 0.25;
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
}

void Necromancer::updateBasicAttributes() {
    setAttackDamage(12 + 7*getStats().getIntelligence() + 2*getStats().getStrength());
    setSummonChance(getStats().getIntelligence() * 4 / 7);
}

// Mekanisme ketika char level up
void Necromancer::levelUp() {
    setMasteryCost(getMasteryCost() + 5);
    setExp(0);
    stats.setStrength(stats.getStrength() * 1.2);
    stats.setAgility(stats.getAgility() * 1.5);
    stats.setIntelligence(stats.getIntelligence() * 2);
    Unit::updateBasicAttributes(); 
    updateBasicAttributes();
    Character::reset();

}


