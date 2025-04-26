#include "../include/EffectHealth.hpp"


EffectHealth::EffectHealth(const std::string& name, const std::string& description, double duration, double remainingDuration, int healAmount)
    : Effect(name, description, duration, remainingDuration), healAmount(healAmount) {}

EffectHealth::~EffectHealth() {}

EffectHealth::EffectHealth(EffectHealth& other) 
    : Effect(other), healAmount(other.healAmount) {}

EffectHealth& EffectHealth::operator=(EffectHealth& other) {
    Effect::operator=(other);
    healAmount = other.healAmount;
    return *this;
}

int EffectHealth::getHealAmount() const {
    return healAmount;
}

void EffectHealth::setHealAmount(int healAmount) {
    this->healAmount = healAmount;
}

double EffectHealth::apply(Unit* unit) {
    int currentRegen = unit->getHealthRegen();
    unit->setHealthRegen(currentRegen + healAmount);
    remainingDuration -= 1;
}

void EffectHealth::remove(Unit* unit) {
    int currentRegen = unit->getHealthRegen();
    unit->setHealthRegen(currentRegen - healAmount);
}