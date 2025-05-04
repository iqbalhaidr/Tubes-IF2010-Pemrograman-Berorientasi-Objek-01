#include "../include/unit.hpp"

#include <iostream>
#include <string>
using namespace std;

Unit::Unit(string name, int strength, int agility, int intelligence, int level)
    : stats(strength, agility, intelligence), name(name) {
    updateBasicAttributes();
    this->currentHealth = maxHealth;
    this->currentMana = maxMana;
    this->level = level;
    std::cout << "[DEBUG] Keluar constructor Unit" << std::endl;
}

Unit::~Unit() {
    for (Effect* effect : activeEffects) {
        delete effect;
    }
    activeEffects.clear();
}

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
    // std::cout << "baseDamage: " << baseDamage << std::endl;
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
    if (this->isChar = true) {
        Item* weapon = inventory.getEquippedItem("WEAPON");
        if (weapon != nullptr) {
            totalDamage += weapon->getFinalStat();  // total damage + weapon damage
            cout << "Weapon name: " << weapon->getName() << std::endl;
            std::cout << "Weapon damage: " << weapon->getFinalStat() << std::endl;
        }

        Item* pendant = inventory.getEquippedItem("PENDANT");
        if (pendant != nullptr) {
            totalDamage += pendant->getFinalStat();  // total damage + weapon damage
        }
    }
    // cout << "totalDamage sblm lvl: " << totalDamage << endl;
    // cout << "baseDamage: " << baseDamage << endl;
    totalDamage *= getLevelFactor(target);  // total damage * level factor

    return totalDamage;
}
void Unit::attack(Unit& target, Inventory& inventory) {
    // std::cout << "attack: " << attackDamage << std::endl;
    std::cout << name << " attacks " << target.getName() << " sebesar " << calculateDamage(target, attackDamage, inventory) << std::endl;
    target.takeDamage(calculateDamage(target, attackDamage, inventory), inventory);
}

void Unit::takeDamage(int damage, Inventory& inventory) {
    // std::cout << "damage from takeDamage(): " << damage << std::endl;
    int defence = 0;  // damage reduction
    if (this->isChar = true) {
        Item* armorHead = inventory.getEquippedItem("ARMOR_HEAD");
        if (armorHead != nullptr) {
            defence += armorHead->getFinalStat();
        }

        Item* armorBody = inventory.getEquippedItem("ARMOR_BODY");
        if (armorBody != nullptr) {
            defence += armorBody->getFinalStat();
        }

        Item* armorFoot = inventory.getEquippedItem("ARMOR_FOOT");
        if (armorFoot != nullptr) {
            defence += armorFoot->getFinalStat();
        }
    }

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
    std::cout << name << " Defence: " << defence << std::endl;
    damage -= defence;
    if (damage < 0) damage = 0;
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

void Unit::useSkill(Skill* skill, Unit& target, Inventory& inventory) {
    cout << "Using skill: " << skill->getName() << endl;
    cout << "Skill effect: " << skill->getEffects()[0]->getName() << endl;
    cout << "Skill damage:" << skill->getDamage() << endl;

    // cek skill ada di vector skill atau tidak
    bool isSkillValid = std::find(skills.begin(), skills.end(), skill) != skills.end();
    if (!isSkillValid) {
        throw InvalidSkill("Skill tidak terdapat pada daftar skill yang dimiliki character");
    }

    if (currentMana < skill->getManaCost()) {
        throw ManaNotEnough("Not enough mana to use skill: " + skill->getName());
    }
    if ((rand() % 100 + 1) > skill->getskillChance()) {
        std::cout << "Skill tidak mengenai target" << std::endl;
        return;
    }
    std::cout << "Skill mengenai target" << std::endl;
    currentMana -= skill->getManaCost();
    int totalDamage = skill->getDamage();
    // cout << "TOTAL DAMAGE: " << skill->getDamage() << endl;
    // cout << "MANA: " << currentMana << endl;

    for (Effect* effect : skill->effects) {
        if ((effect->isTurn() || effect->isTurnBased()) ||
            (effect->isDamage() && effect->getName() == "Infernal Curse") ||
            (effect->isDefensive() &&
             effect->getName() ==
                 "Infernal Curse")) {  // kasus crit masukin efek crit dari
                                       // skill ke vector dulu
            // std::cout << "masuk if pertama unit.cpp: " << effect->getName()
                      //<< std::endl;
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

    // std::cout << "Skill damage: " << totalDamage << std::endl;
    target.takeDamage(totalDamage, inventory);
}

void Unit::addSkill(Skill* skill) { skills.push_back(skill); }
void Unit::removeSkill(Skill* skill) {
    auto it = find(skills.begin(), skills.end(), skill);
    if (it != skills.end()) {
        skills.erase(it);  //
    }
}

void Unit::addActiveEffect(Effect* effect) {
    activeEffects.push_back(effect->clone());
}

void Unit::removeActiveEffect(Effect* activeEffect) { //akhir
    auto it = find(activeEffects.begin(), activeEffects.end(), activeEffect);
    if (it != activeEffects.end()) {
        activeEffect->remove(this);
        activeEffects.erase(it);
    }
}

void Unit::applyActiveEffect() { //awal
    for (auto& activeEffect : activeEffects) {
        if (activeEffect->isHealthRegen() || activeEffect->isManaRegen()) {
            if (activeEffect->isHealthRegen()) {
                std::cout << "Health regen effect called: "
                          << activeEffect->getName() << std::endl;
                heal(activeEffect->apply(this));
            } else if (activeEffect->isManaRegen()) {
                std::cout << "Mana regen effect called: "
                          << activeEffect->getName() << std::endl;
                restoreMana(activeEffect->apply(this));
            }
        } else if (activeEffect->isPoison()) {
            currentHealth -= activeEffect->apply(this);
        } else if (activeEffect->isManaReduc()) {
            currentMana -= activeEffect->apply(this);
        } else if (activeEffect->isTurn()) {
            int stunReturn = activeEffect->apply(this);
        }
        activeEffect->decreaseRemainingDuration();
    }
}

void Unit::updateBasicAttributes() {
    setMaxHealth(100 + 22 * getStats().getStrength());
    setHealthRegen(1.6 * getStats().getStrength());
    setMaxMana(60 + 12 * getStats().getIntelligence());
    setManaRegen(1.3 * getStats().getIntelligence());
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
                            damageOther->setRemainingDuration(0);
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
                            defensiveOther->setRemainingDuration(0);
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