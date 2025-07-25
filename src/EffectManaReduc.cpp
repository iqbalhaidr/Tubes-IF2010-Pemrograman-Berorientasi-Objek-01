#include "../include/EffectManaReduc.hpp"
#include "../include/unit.hpp"

EffectManaReduc::EffectManaReduc(const std::string& name, const std::string& description, double duration, double remainingDuration, double manaAmount, int chance, bool isThrowable):
        EffectTurnBasedBased(name, description, duration, remainingDuration, chance, isThrowable), manaAmount(manaAmount){}

EffectManaReduc::~EffectManaReduc(){}

EffectManaReduc::EffectManaReduc(const EffectManaReduc& other) 
    : EffectTurnBasedBased(other), manaAmount(other.manaAmount) {}

EffectManaReduc& EffectManaReduc::operator=(EffectManaReduc& other) {
    EffectTurnBasedBased::operator=(other);
    manaAmount = other.manaAmount;
    return *this;
}

double EffectManaReduc::getManaAmount() const {
    return manaAmount;
}

void EffectManaReduc::setManaAmount(int manaAmount) {
    this->manaAmount = manaAmount;
}

double EffectManaReduc::apply(Unit* unit) {
    // remainingDuration = remainingDuration - 1;
    int randomValue = rand() % 100 + 1;
    if (randomValue > chance) {
        return manaAmount; 
    }
    return 0;
}

void EffectManaReduc::remove(Unit* unit) {
}

bool EffectManaReduc::isManaReduc(){
    return true;
}