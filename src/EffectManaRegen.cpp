#include "../include/EffectManaRegen.hpp"
#include "../include/Unit.hpp"


EffectManaRegen::EffectManaRegen(const std::string& name, const std::string& description, double duration, double remainingDuration, int manaAmount)
    : EffectTurnBasedBased(name, description, duration, remainingDuration), manaAmount(manaAmount) {}
EffectManaRegen::~EffectManaRegen() {}
EffectManaRegen::EffectManaRegen(const EffectManaRegen& other) 
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
    return manaAmount;
}


Effect* EffectManaRegen::clone() const{
    return new EffectManaRegen(*this);
}

void EffectManaRegen::remove(Unit* unit) {
}

bool EffectManaRegen::isManaRegen() {
    return true;
}