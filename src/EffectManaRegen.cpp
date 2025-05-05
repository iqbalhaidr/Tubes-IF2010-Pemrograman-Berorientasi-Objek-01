#include "../include/EffectManaRegen.hpp"
#include "../include/unit.hpp"


EffectManaRegen::EffectManaRegen(const std::string& name, const std::string& description, double duration, double remainingDuration, int manaAmount, int chance, bool isThrowable)
    : EffectTurnBasedBased(name, description, duration, remainingDuration, chance, isThrowable), manaAmount(manaAmount) {}
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
    // remainingDuration = remainingDuration - 1;
    int randomValue = rand() % 100 + 1;
    if (randomValue > chance) {
        return manaAmount;
    }

    return 0;
}


Effect* EffectManaRegen::clone() const{
    return new EffectManaRegen(*this);
}

void EffectManaRegen::remove(Unit* unit) {
}

bool EffectManaRegen::isManaRegen() {
    return true;
}