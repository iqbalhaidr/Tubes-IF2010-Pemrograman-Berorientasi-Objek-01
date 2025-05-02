#include "../include/EffectHealthRegen.hpp"
#include "../include/unit.hpp"

EffectHealthRegen::EffectHealthRegen(const std::string& name, const std::string& description, double duration, double remainingDuration, int healAmount)
    : EffectTurnBasedBased(name, description, duration, remainingDuration), healAmount(healAmount) {}
EffectHealthRegen::~EffectHealthRegen() {}
EffectHealthRegen::EffectHealthRegen(const EffectHealthRegen& other) 
    : EffectTurnBasedBased(other), healAmount(other.healAmount) {}
EffectHealthRegen& EffectHealthRegen::operator=(EffectHealthRegen& other) {
    EffectTurnBasedBased::operator=(other);
    healAmount = other.healAmount;
    return *this;
}

int EffectHealthRegen::getHealAmount() const {
    return healAmount;
}
void EffectHealthRegen::setHealAmount(int healAmount) {
    this->healAmount = healAmount;
}
double EffectHealthRegen::apply(Unit* unit) {
    // remainingDuration = remainingDuration - 1;
    return healAmount; 
}

Effect* EffectHealthRegen::clone() const{
    return new EffectHealthRegen(*this);
}

void EffectHealthRegen::remove(Unit* unit) {
}

bool EffectHealthRegen::isHealthRegen() {
    return true;
}