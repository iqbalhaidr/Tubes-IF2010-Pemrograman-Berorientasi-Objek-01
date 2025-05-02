#include "../include/unit.hpp"

#include <iostream>
#include <string>
using namespace std;

Unit::Unit(string name, int strength, int agility, int intelligence, int level)
    : stats(strength, agility, intelligence) {
    this->name = name;
    updateBasicAttributes();
    this->currentHealth = maxHealth;
    this->currentMana = maxMana;
    this->level = level;
}

Unit::~Unit() {}

string Unit::getName() const { return name; }
int Unit::getCurrentHealth() const { return currentHealth; }
int Unit::getMaxHealth() const { return maxHealth; }
int Unit::getHealthRegen() const { return healthRegen; }
int Unit::getCurrentMana() const { return currentMana; }
int Unit::getMaxMana() const { return maxMana; }
int Unit::getManaRegen() const { return manaRegen; }
int Unit::getAttackDamage() const { return attackDamage; }
int Unit::getLevel() const { return level; }
int Unit::getLevelFactor(Unit& target) const {
    return 1 + (abs(this->level - target.level)) * 0.05;
}
bool Unit::getTurnEffectStatus(string turnEffectName) const {
    for (const auto& effect : activeEffects) {
        if (effect->getName().find(turnEffectName) !=
            std::string::npos) {  // contains name
            return true;
        }
    }
    return false;
}

Stats Unit::getStats() const { return stats; }
vector<Skill*> Unit::getSkills() const { return skills; }  // TEMPORARY
vector<Effect*> Unit::getActiveEffects() const {
    return activeEffects;
}  // TEMPORARY

void Unit::setName(string name) { this->name = name; }
void Unit::setCurrentHealth(int currentHealth) {
    this->currentHealth = currentHealth;
}
void Unit::setMaxHealth(int maxHealth) { this->maxHealth = maxHealth; }
void Unit::setHealthRegen(int healthRegen) { this->healthRegen = healthRegen; }
void Unit::setCurrentMana(int currentMana) { this->currentMana = currentMana; }
void Unit::setMaxMana(int maxMana) { this->maxMana = maxMana; }
void Unit::setManaRegen(int manaRegen) { this->manaRegen = manaRegen; }
void Unit::setAttackDamage(int attackDamage) {
    this->attackDamage = attackDamage;
}

void Unit::setStats(int strength, int agility, int intelligence) {
    stats.setStrength(strength);
    stats.setAgility(agility);
    stats.setIntelligence(intelligence);
}
int Unit::calculateDamage(Unit& target, int baseDamage, Inventory& inventory) {
    int totalDamage = 0;
    for (const auto& ActiveEffect : getCombinedEffect(activeEffects)) {
        if (ActiveEffect->isDamage()) {
            if (ActiveEffect->getName() == "Infernal Curse") {
                totalDamage -= ActiveEffect->apply(this);
            } else {
                totalDamage += ActiveEffect->apply(this);
            }
        }
    }
    if (totalDamage < 0) totalDamage = 0;
    totalDamage += baseDamage;  // total damage = base damage + critical damage
    // cout << "totalDamage sblm wepen: " << totalDamage << endl;
    Item* weapon = inventory.getEquippedItem("WEAPON");

    if (weapon != nullptr) {
        totalDamage += weapon->getFinalStat();  // total damage + weapon damage
    }
    // cout << "totalDamage sblm lvl: " << totalDamage << endl;
    // cout << "baseDamage: " << baseDamage << endl;
    totalDamage *= getLevelFactor(target);  // total damage * level factor

    return totalDamage;
}
void Unit::attack(Unit& target, Inventory& inventory) {
    std::cout << name << " attacks " << target.getName() << " sebesar "
              << calculateDamage(target, attackDamage, inventory) << std::endl;
    target.takeDamage(calculateDamage(target, attackDamage, inventory));
}

void Unit::takeDamage(int damage) {
    int defence = 0;  // damage reduction
    for (const auto& activeEffect : getCombinedEffect(activeEffects)) {
        if (activeEffect->isDefensive()) {
            if (activeEffect->getName() == "Infernal Curse") {
                defence -= activeEffect->apply(this);
            } else {
                defence += activeEffect->apply(this);
            }
        }
    }
    if (defence < 0) defence = 0;
    damage *= 1 - defence;
    std::cout << name << " takes " << damage << " damage!\n";
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
    cout << "Using skill: " << skill->getName() << endl;
    if (currentMana < skill->getManaCost()) {
        cout << "Not enough mana to use " << skill->getName() << endl;
        return;
    }
    // if ((rand() % 100 + 1) > skill->getskillChance()) {
    //     return;
    // }
    // if ((rand() % 100 + 1) > skill->getskillChance()) {
    //     std::cout << "Skill tidak mengenai target" << std::endl;
    //     return;
    // }
    std::cout << "Skill mengenai target" << std::endl;
    currentMana -= skill->getManaCost();
    int totalDamage = skill->getDamage();
    cout << "TOTAL DAMAGE: " << skill->getDamage() << endl;
    cout << "MANA: " << currentMana << endl;

    for (Effect* effect : skill->effects) {
        if ((effect->isTurn() || effect->isTurnBased()) ||
            (effect->isDamage() && effect->getName() == "Infernal Curse") ||
            (effect->isDefensive() &&
             effect->getName() ==
                 "Infernal Curse")) {  // kasus crit masukin efek crit dari
                                       // skill ke vector dulu
            target.addActiveEffect(effect);
        } else if (effect->isDefensive() || effect->isDamage()) {
            this->addActiveEffect(effect);
        } else if (effect->isHealth()) {
            heal(effect->apply(this));
        }
    }

    for (Effect* ActiveEffect : getCombinedEffect(activeEffects)) {
        if (EffectDamage* damageEffect =
                dynamic_cast<EffectDamage*>(ActiveEffect)) {
            if (damageEffect->getName() == "Brittle" &&
                (damageEffect->getDuration() ==
                 damageEffect->getRemainingDuration())) {
                continue;
            }
            totalDamage += ActiveEffect->apply(this);
        }
    }

    std::cout << "Skill damage: " << totalDamage << std::endl;
    target.takeDamage(totalDamage);
}

void Unit::addSkill(Skill* skill) { skills.push_back(skill); }
void Unit::removeSkill(Skill* skill) {
    auto it = find(skills.begin(), skills.end(), skill);
    if (it != skills.end()) {
        skills.erase(it);  //
    }
}

void Unit::addActiveEffect(Effect* effect) { activeEffects.push_back(effect); }

void Unit::removeActiveEffect(Effect* activeEffect) {
    auto it = find(activeEffects.begin(), activeEffects.end(), activeEffect);
    if (it != activeEffects.end()) {
        activeEffect->remove(this);
        activeEffects.erase(it);
    }
}

void Unit::applyActiveEffect() {
    for (auto& activeEffect : activeEffects) {
        if (activeEffect->isHealthRegen() || activeEffect->isManaRegen()) {
            if (activeEffect->isHealthRegen()) {
                heal(activeEffect->apply(this));
            } else if (activeEffect->isManaRegen()) {
                restoreMana(activeEffect->apply(this));
            }
        } else if (activeEffect->isPoison()) {
            currentHealth -= activeEffect->apply(this);
        } else if (activeEffect->isManaReduc()) {
            currentMana -= activeEffect->apply(this);
        } else if (activeEffect->isTurn()) {
            int stunReturn = activeEffect->apply(this);
        }
    }
}

void Unit::updateBasicAttributes() {
    setMaxHealth(100 + 22 * getStats().getStrength());
    setHealthRegen(10 * getStats().getStrength());
    setMaxMana(60 + 12 * getStats().getIntelligence());
    setManaRegen(5 * getStats().getIntelligence());
}

vector<Effect*> Unit::getCombinedEffect(
    const vector<Effect*>& activeEffects) const {
    vector<Effect*> combinedEffects;
    vector<bool> processed(activeEffects.size(), false);

    for (size_t i = 0; i < activeEffects.size(); i++) {
        if (processed[i]) {
            continue;
        }

        Effect* baseEffect = activeEffects[i]->clone();
        processed[i] = true;

        for (size_t j = i + 1; j < activeEffects.size(); j++) {
            if (!processed[j] &&
                baseEffect->getName() == activeEffects[j]->getName()) {
                if (auto regenBase =
                        dynamic_cast<EffectHealthRegen*>(baseEffect)) {
                    if (auto regenOther = dynamic_cast<EffectHealthRegen*>(
                            activeEffects[j])) {
                        regenBase->setHealAmount(regenBase->getHealAmount() +
                                                 regenOther->getHealAmount());
                        processed[j] = true;
                    }
                } else if (auto manaBase =
                               dynamic_cast<EffectManaRegen*>(baseEffect)) {
                    if (auto manaOther =
                            dynamic_cast<EffectManaRegen*>(activeEffects[j])) {
                        manaBase->setManaAmount(manaBase->getManaAmount() +
                                                manaOther->getManaAmount());
                        processed[j] = true;
                    }
                } else if (auto turnBasedBase =
                               dynamic_cast<EffectTurnBasedBased*>(
                                   baseEffect)) {
                    if (auto turnBasedOther =
                            dynamic_cast<EffectTurnBasedBased*>(
                                activeEffects[j])) {
                        turnBasedBase->setDuration(
                            max(turnBasedBase->getDuration(),
                                turnBasedOther->getDuration()));
                        processed[j] = true;
                    }
                } else if (auto damageBase =
                               dynamic_cast<EffectDamage*>(baseEffect)) {
                    if (auto damageOther =
                            dynamic_cast<EffectDamage*>(activeEffects[j])) {
                        if (damageBase->getName() == "Infernal Curse") {
                            damageBase->setRemainingDuration(
                                damageBase->getDuration());
                        } else {
                            damageBase->setChance(damageBase->getChance() +
                                                  damageOther->getChance());
                            damageBase->setDamage(damageBase->getDamage() +
                                                  damageOther->getDamage());
                        }
                        processed[j] = true;
                    }
                } else if (auto defensiveBase =
                               dynamic_cast<EffectDefensive*>(baseEffect)) {
                    if (auto defensiveOther =
                            dynamic_cast<EffectDefensive*>(activeEffects[j])) {
                        if (defensiveBase->getName() == "Infernal Curse") {
                            defensiveBase->setRemainingDuration(
                                defensiveBase->getDuration());
                        } else {
                            defensiveBase->setChance(
                                defensiveBase->getChance() +
                                defensiveOther->getChance());
                            defensiveBase->setDefense(
                                defensiveBase->getDefense() +
                                defensiveOther->getDefense());
                        }
                        processed[j] = true;
                    }
                }
            }
        }
        combinedEffects.push_back(baseEffect);
    }
    return combinedEffects;
}