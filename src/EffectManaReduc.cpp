#include "../include/EffectManaReduc.hpp"
#include "../include/Unit.hpp"

EffectManaReduc::EffectManaReduc(const std::string& name, const std::string& description, double duration, double remainingDuration, double manaAmount):
        EffectTurnBasedBased(name, description, duration, remainingDuration), manaAmount(manaAmount){}

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
    return manaAmount; 
}

void EffectManaReduc::remove(Unit* unit) {
}