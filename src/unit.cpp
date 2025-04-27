#include "unit.hpp"
#include <iostream>
#include <string>
using namespace std;

Unit::Unit(string name, int strength, int agility, int intelligence) : stats(strength, agility, intelligence) {
    setName(name);
    updateBasicAttributes();     
    this->turnEffectstatus = {
        {"stun", false},
        {"disable", false}
    };
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
map<string, bool> Unit::getTurnEffectStatus() const { return turnEffectstatus;}
Stats Unit::getStats() const { return stats;}
vector<Skill*> Unit::getSkills() const { return skills;} // TEMPORARY
vector<Effect*> Unit::getEffects() const { return effects;} // TEMPORARY

void Unit::setName(string name) { this->name = name;}
void Unit::setCurrentHealth(int currentHealth) { this->currentHealth = currentHealth;}
void Unit::setMaxHealth(int maxHealth) { this->maxHealth = maxHealth;}
void Unit::setHealthRegen(int healthRegen) { this->healthRegen = healthRegen;}
void Unit::setCurrentMana(int currentMana) { this->currentMana = currentMana;}
void Unit::setMaxMana(int maxMana) { this->maxMana = maxMana;}
void Unit::setManaRegen(int manaRegen) { this->manaRegen = manaRegen;}
void Unit::setAttackDamage(int attackDamage) { this->attackDamage = attackDamage;}
void Unit::setTurnEffectStatus(string turnEffect) {
    if (turnEffectstatus.find(turnEffect) != turnEffectstatus.end()) {
        turnEffectstatus[turnEffect] = true; 
    } 
      
}
void Unit::setStats(int strength, int agility, int intelligence) {
    stats.setStrength(strength);
    stats.setAgility(agility);
    stats.setIntelligence(intelligence);
}
int Unit::calculateDamage(int baseDamage, Inventory& inventory) {
    int totalDamage = 1;
    for (const auto& effect : effects) {
        if (effect->isTurn() && effect->getName() == "stun") {
            return;
        } 
        else if (effect->isDamage()) {
            totalDamage += effect->apply(this);
            if (effect->getRemainingDuration() <= 0) {
                removeEffect(effect); 
            } 
        }
    }
    int weaponDamage = inventory.getEquippedItem("weapon")->getBaseStat();
    totalDamage *= (baseDamage + weaponDamage);

    return totalDamage;
}
void Unit::attack(Unit& target, Inventory& inventory) {
    target.takeDamage(calculateDamage(attackDamage, inventory)); 
}

void Unit::takeDamage(int damage) {
    for (const auto& effect : effects) {
        if (effect->isDamage()) {
            damage -= effect->apply(this);
        }
    }
    currentHealth -= damage;
    if (currentHealth < 0) {
        currentHealth = 0;
    }
}

void Unit::heal(int amount) {
    if (amount < 0) {
        amount = 0;
    }
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

void Unit::useSkill(Skill* skill, Unit& target) {
    if (currentMana < skill->getManaCost()) {
        cout << "Not enough mana to use " << skill->getName() << endl;
        return;
    }
    currentMana -= skill->getManaCost(); 
    // target.takeDamage(skill->getDamage()); // TEMPORARY
    // for (const auto& skill->effect : effects) {
        // target.addEffect(skill->effect); 
    // }
    // logika penggunaan skill
    // 1. cek mana cukup untuk useskill
    // 2. kurangi mana
    // 3. attack proses damage

    // 4. apply efek
}

void Unit::addSkill(Skill* skill) {
    skills.push_back(skill); // TEMPORARY
}
void Unit::removeSkill(Skill* skill) {
    auto it = find(skills.begin(), skills.end(), skill);
    if (it != skills.end()) {
        skills.erase(it); // 
    }
}

void Unit::addEffect(Effect* effect) {
    effects.push_back(effect); 
}

void Unit::removeEffect(Effect* effect) {
    auto it = find(effects.begin(), effects.end(), effect);
    if (it != effects.end()) {
        effects.erase(it); 
    }
}


void Unit::applyEffect() {
    for (const auto& effect : effects) {
        if (effect->isTurnBased()) {
            effect->apply(this); 
        }
        if (effect->getRemainingDuration() <= 0) {
            removeEffect(effect);
        } 
    }
}

void Unit::updateBasicAttributes() {
    setMaxHealth(100 + 22 * getStats().getStrength());
    setHealthRegen(10 * getStats().getStrength());
    setMaxMana(60 + 12 * getStats().getIntelligence());
    setManaRegen(5 * getStats().getIntelligence());
    // this->attackDamage = 10 + 5 * getStats().getAgility();
}