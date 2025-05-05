#include "../include/EffectHealth.hpp"
#include "../include/unit.hpp"



EffectHealth::EffectHealth(const std::string& name, const std::string& description, double duration, double remainingDuration, int chance, int healAmount, bool isThrowable)
    : Effect(name, description, duration, remainingDuration, chance, isThrowable), healAmount(healAmount){}

EffectHealth::~EffectHealth() {}

EffectHealth::EffectHealth(const EffectHealth& other) 
    : Effect(other), healAmount(other.healAmount) {}

EffectHealth& EffectHealth::operator=(EffectHealth& other) {
    Effect::operator=(other);
    healAmount = other.healAmount;
    chance = other.chance;
    return *this;
}

int EffectHealth::getHealAmount() const {
    return healAmount;
}

void EffectHealth::setHealAmount(int healAmount) {
    this->healAmount = healAmount;
}

double EffectHealth::getChance() const {
    return chance;
}

void EffectHealth::setChance(double chance) {
    this->chance = chance;
}

double EffectHealth::apply(Unit* unit) {
    // remainingDuration -= 1;
    int randomValue = rand() % 100 + 1;
    int currentRegen = unit->getHealthRegen();
    baseHealAmount = currentRegen;
    if (randomValue > chance) {
        return currentRegen; 
    }
    return currentRegen + healAmount * currentRegen / 100;
    // unit->setHealthRegen(currentRegen + healAmount);
    // return 0;
}

void EffectHealth::remove(Unit* unit) {
    // int currentRegen = unit->getHealthRegen();
    // return currentRegen - (baseHealAmount * currentRegen / 100);
}



Effect* EffectHealth::clone() const {
    return new EffectHealth(*this);
}

bool EffectHealth::isHealth() {
    return true;
}