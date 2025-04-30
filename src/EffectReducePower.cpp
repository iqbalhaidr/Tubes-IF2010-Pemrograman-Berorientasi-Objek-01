#include "../include/EffectReducePower.hpp"

EffectReducePower::EffectReducePower(const std::string& name, const std::string& description, double duration, double remainingDuration, double chance, double damage)
    : Effect(name, description, duration, remainingDuration), chance(chance), damage(damage) {}

EffectReducePower::~EffectReducePower() {}

EffectReducePower::EffectReducePower(const EffectReducePower& other) 
    : Effect(other), chance(other.chance), damage(other.damage) {}

EffectReducePower& EffectReducePower::operator=(EffectReducePower& other) {
    Effect::operator=(other);
    chance = other.chance;
    damage = other.damage;
    return *this;
}

double EffectReducePower::getChance() const {
    return chance;
}

double EffectReducePower::getDamage() const {
    return damage;
}

void EffectReducePower::setChance(double chance) {
    this->chance = chance;
}

void EffectReducePower::setDamage(double damage) {
    this->damage = damage;
}

double EffectReducePower::apply(Unit* unit) {
    int random = rand() % 100 + 1;
    remainingDuration -= 1;
    if (random <= chance){
        return damage;
    }

    else{
        return 0;    
    }
}

bool EffectReducePower::isReducePower(){return true;}