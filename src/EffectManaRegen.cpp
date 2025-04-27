#include "../include/EffectManaRegen.hpp"

EffectManaRegen::EffectManaRegen(const std::string& name, const std::string& description, double duration, double remainingDuration, int manaAmount)
    : EffectTurnBasedBased(name, description, duration, remainingDuration), manaAmount(manaAmount) {}
EffectManaRegen::~EffectManaRegen() {}
EffectManaRegen::EffectManaRegen(EffectManaRegen& other) 
    : EffectTurnBasedBased(other), manaAmount(other.manaAmount) {}
EffectManaRegen& EffectManaRegen::operator=(EffectManaRegen& other) {
    EffectTurnBasedBased::operator=(other);
    manaAmount = other.manaAmount;
    return *this;
}
int EffectManaRegen::getManaAmount() const {
    return manaAmount;
}
void EffectManaRegen::setManaAmount(int manaAmount) {
    this->manaAmount = manaAmount;
}

double EffectManaRegen::apply(Unit* unit) {
    int currentRegen = unit->getManaRegen();
    unit->setManaRegen(currentRegen + manaAmount);
    remainingDuration -= 1;
    return 0; 
}

