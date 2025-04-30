#include "../include/EffectReducePower.hpp"

EffectReducePower::EffectReducePower(const std::string& name, const std::string& description, double duration, double remainingDuration, double chance, double amount)
    : Effect(name, description, duration, remainingDuration), chance(chance), amount(amount) {}

EffectReducePower::~EffectReducePower() {}

EffectReducePower::EffectReducePower(const EffectReducePower& other) 
    : Effect(other), chance(other.chance), amount(other.amount) {}

EffectReducePower& EffectReducePower::operator=(EffectReducePower& other) {
    Effect::operator=(other);
    chance = other.chance;
    amount = other.amount;
    return *this;
}

double EffectReducePower::getChance() const {
    return chance;
}

double EffectReducePower::getamount() const {
    return amount;
}

void EffectReducePower::setChance(double chance) {
    this->chance = chance;
}

void EffectReducePower::setamount(double amount) {
    this->amount = amount;
}

double EffectReducePower::apply(Unit* unit) {
    int random = rand() % 100 + 1;
    remainingDuration -= 1;
    if (random <= chance){
        return amount;
    }

    else{
        return 0;    
    }
}

bool EffectReducePower::isReducePower(){return true;}