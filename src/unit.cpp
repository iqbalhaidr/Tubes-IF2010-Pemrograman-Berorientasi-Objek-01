#include "unit.hpp"
#include <iostream>
#include <string>
using namespace std;

Unit::Unit(string name, int strength, int agility, int intelligence) : stats(strength, agility, intelligence) {
    setName(name);
    updateBasicAttributes();     
    this->turnActiveEffectstatus = {
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
map<string, bool> Unit::getTurnActiveEffectStatus() const { return turnActiveEffectstatus;}
Stats Unit::getStats() const { return stats;}
vector<Skill*> Unit::getSkills() const { return skills;} // TEMPORARY
vector<Effect*> Unit::getActiveEffects() const { return activeEffects;} // TEMPORARY

void Unit::setName(string name) { this->name = name;}
void Unit::setCurrentHealth(int currentHealth) { this->currentHealth = currentHealth;}
void Unit::setMaxHealth(int maxHealth) { this->maxHealth = maxHealth;}
void Unit::setHealthRegen(int healthRegen) { this->healthRegen = healthRegen;}
void Unit::setCurrentMana(int currentMana) { this->currentMana = currentMana;}
void Unit::setMaxMana(int maxMana) { this->maxMana = maxMana;}
void Unit::setManaRegen(int manaRegen) { this->manaRegen = manaRegen;}
void Unit::setAttackDamage(int attackDamage) { this->attackDamage = attackDamage;}
void Unit::setTurnActiveEffectStatus(string turnActiveEffect) {
    if (turnActiveEffectstatus.find(turnActiveEffect) != turnActiveEffectstatus.end()) {
        turnActiveEffectstatus[turnActiveEffect] = true; 
    } 
      
}
void Unit::setStats(int strength, int agility, int intelligence) {
    stats.setStrength(strength);
    stats.setAgility(agility);
    stats.setIntelligence(intelligence);
}
int Unit::calculateDamage(Unit& target, int baseDamage, Inventory& inventory) {
    int totalDamage = 1;
    for (const auto& ActiveEffect : activeEffects) {
        if (ActiveEffect->isDamage()) {
            totalDamage += ActiveEffect->apply(this);
            if (ActiveEffect->getRemainingDuration() <= 0) {
                removeActiveEffect(ActiveEffect); 
            } 
        }
    }
    int weaponDamage = inventory.getEquippedItem("weapon")->getBaseStat();
    totalDamage *= (baseDamage + weaponDamage);

    return totalDamage;
}
void Unit::attack(Unit& target, Inventory& inventory) {
    target.takeDamage(calculateDamage(target, attackDamage, inventory)); 
}

void Unit::takeDamage(int damage) {
    for (const auto& activeEffect : activeEffects) {
        if (activeEffect->isDefensive()) {
            damage -= activeEffect->apply(this);
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

    target.takeDamage(skill->getDamage()); 
    for (const auto& effect : skill->effects) {
        if (rand() % 100 < skill->getEffectChance())
        target.addActiveEffect(effect); 
    }
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

void Unit::addActiveEffect(Effect* effect) {
    activeEffects.push_back(effect); 
}

void Unit::removeActiveEffect(Effect* activeEffect) {
    auto it = find(activeEffects.begin(), activeEffects.end(), activeEffect);
    if (it != activeEffects.end()) {
        activeEffects.erase(it); 
    }
}

void Unit::addItemEffect(Effect* effect) {
    itemEffects.push_back(effect);
}

void Unit::removeItemEffect(Effect* itemEffect) {
    auto it = find(itemEffects.begin(), itemEffects.end(), itemEffect);
    if (it != itemEffects.end()) {
        itemEffects.erase(it); 
    }
}

void Unit::applyActiveEffect() {
    for (const auto& activeEffect : activeEffects) {
        if (activeEffect->isTurnBased()) {
            currentHealth -= activeEffect->apply(this); 
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