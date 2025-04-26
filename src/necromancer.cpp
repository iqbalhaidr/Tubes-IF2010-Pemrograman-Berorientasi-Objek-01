#include "necromancer.hpp"

Necromancer::Necromancer(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence,  int level, int exp, string mastery, int gold, double summonChance)
: Character(name, maxHealth, healthRegen, maxMana, manaRegen, attackDamage, strength, agility, intelligence, level, exp, gold, "Necromancer") {
    this->summonChance = summonChance;
    this->summonTurns = 0; 
    this->summons = false;
}

Necromancer::~Necromancer() {
}

double Necromancer::getSummonChance() const { return summonChance;}
void Necromancer::setSummonChance(double summonChance) { this->summonChance = summonChance;}

void Necromancer::attack(Unit& target) {
    if (!summons && rand() % 100 < summonChance) {
        summons = true;
        summonTurns = 4;
        Unit::attack(target); 
    }
    if (summons) {
        summonTurns--;
        if (summonTurns == 0) {
            summons = false;
        }
        // total damage = damage + stats.getIntelligence()
        // target.takeDamage(total damage); // damage dari minion
    }
}

void Necromancer::useSkill(string& skill, Unit& target) {
    Unit::useSkill(skill, target); 
    target.takeDamage(getStats().getIntelligence() * 0.25);
    currentHealth += getStats().getIntelligence() * 0.25;
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
}

void Necromancer::levelUp() {
    masteryCost += 5; 
    stats.setStrength(stats.getStrength() * 1.2);
    stats.setAgility(stats.getAgility() * 1.5);
    stats.setIntelligence(stats.getIntelligence() * 2);
}


