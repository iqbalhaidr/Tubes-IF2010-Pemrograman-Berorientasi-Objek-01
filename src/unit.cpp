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
    for (const auto& ActiveEffect : getCombinedEffect(activeEffects)) {
        if (auto* damageEffect = dynamic_cast<EffectDamage*>(ActiveEffect)) {
            if (rand() % 100 < damageEffect->getChance()) {
                totalDamage += ActiveEffect->apply(this);
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
    for (const auto& activeEffect : getCombinedEffect(activeEffects)) {
        if (auto* defensiveEffect = dynamic_cast<EffectDamage*>(activeEffect)) {
            if (rand() % 100 < defensiveEffect->getChance()) {
                damage *= 1 - activeEffect->apply(this);
            }
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
    int totalDamage = skill->getDamage();

    for (const auto& effect : skill->effects) {
        if (effect->isTurn() || effect->isTurnBased()) { // kasus crit masukin efek crit dari skill ke vector dulu
            target.addActiveEffect(effect); 
        } else if (effect->isDefensive() || effect->isDamage()) {
            this->addActiveEffect(effect);
        } else if(effect->isHealth()) {
            setHealthRegen(effect->apply(this));
        }
        
    }

    for (const auto& ActiveEffect : getCombinedEffect(activeEffects)) {
        if (auto* damageEffect = dynamic_cast<EffectDamage*>(ActiveEffect)) {
            if (rand() % 100 < damageEffect->getChance()) { // mungkin effect crit dari skill yg baru dimasukin + crit dari yg dah ada
                totalDamage += ActiveEffect->apply(this);
            }
        }
    }

    target.takeDamage(totalDamage); 

}

void Unit::addSkill(Skill* skill) {
    skills.push_back(skill); 
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

void Unit::applyActiveEffect() {
    for (auto& activeEffect : activeEffects) {
        if (activeEffect->isHealthRegen() || activeEffect->isManaRegen()) {
            if (activeEffect->isHealthRegen()) {
                setHealthRegen(getHealthRegen() + activeEffect->apply(this));
            }
            else if (activeEffect->isManaRegen()) {
                setManaRegen(getManaRegen() + activeEffect->apply(this));
            }
            if (activeEffect->getRemainingDuration() == 0) {
                activeEffect->remove(this);
            }
        }
        else if (activeEffect->isPoison()) {
            currentHealth -= activeEffect->apply(this);
        }

    }
}


void Unit::updateBasicAttributes() {
    setMaxHealth(100 + 22 * getStats().getStrength());
    setHealthRegen(10 * getStats().getStrength());
    setMaxMana(60 + 12 * getStats().getIntelligence());
    setManaRegen(5 * getStats().getIntelligence());
}

vector<Effect*> Unit::getCombinedEffect(const vector<Effect*>& activeEffects) const {
    vector<Effect*> combinedEffects;
    vector<bool> processed(activeEffects.size(), false);

    for (size_t i = 0; i < activeEffects.size(); i++) {
        if (processed[i]) {
            continue;
        }

        Effect* baseEffect = activeEffects[i]->clone();
        processed[i] = true;

        for (size_t j = i + 1; j < activeEffects.size(); j++) {
            if (!processed[j] && baseEffect->getName() == activeEffects[j]->getName()) {
                if (auto regenBase = dynamic_cast<EffectHealthRegen*>(baseEffect)) {
                    if (auto regenOther = dynamic_cast<EffectHealthRegen*>(activeEffects[j])) {
                        regenBase->setHealAmount(regenBase->getHealAmount() + regenOther->getHealAmount());
                        processed[j] = true;
                    }
                } else if (auto manaBase = dynamic_cast<EffectManaRegen*>(baseEffect)) {
                    if (auto manaOther = dynamic_cast<EffectManaRegen*>(activeEffects[j])) {
                        manaBase->setManaAmount(manaBase->getManaAmount() + manaOther->getManaAmount());
                        processed[j] = true;
                    }
                } else if (auto turnBasedBase = dynamic_cast<EffectTurnBasedBased*>(baseEffect)) {
                    if (auto turnBasedOther = dynamic_cast<EffectTurnBasedBased*>(activeEffects[j])) {

                        turnBasedBase->setDuration(max(turnBasedBase->getDuration(), turnBasedOther->getDuration()));
                        processed[j] = true;
                    }
                } else if (auto damageBase = dynamic_cast<EffectDamage*>(baseEffect)) {
                    if (auto damageOther = dynamic_cast<EffectDamage*>(activeEffects[j])) {
                        damageBase->setChance(damageBase->getChance() + damageOther->getChance());
                        damageBase->setDamage(damageBase->getDamage() + damageOther->getDamage());
                        processed[j] = true;
                    }
                } else if (auto defensiveBase = dynamic_cast<EffectDefensive*>(baseEffect)) {
                    if (auto defensiveOther = dynamic_cast<EffectDefensive*>(activeEffects[j])) {
                        defensiveBase->setChance(defensiveBase->getChance() + defensiveOther->getChance());
                        defensiveBase->setDefense(defensiveBase->getDefense() + defensiveOther->getDefense());
                        processed[j] = true;
                    }
                }
            }
        }
        combinedEffects.push_back(baseEffect);
    }
    return combinedEffects;
}