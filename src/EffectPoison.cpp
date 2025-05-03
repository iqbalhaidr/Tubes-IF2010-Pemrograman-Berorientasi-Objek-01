#include "../include/EffectPoison.hpp"

EffectPoison::EffectPoison(const std::string& name, const std::string& description, double duration, double remainingDuration, double chance, double damage)
    : EffectTurnBasedBased(name, description, duration, remainingDuration), damage(damage), chance(chance) {}
EffectPoison::~EffectPoison() {}
EffectPoison::EffectPoison(const EffectPoison& other) 
    : EffectTurnBasedBased(other), damage(other.damage), chance(other.chance) {}
EffectPoison& EffectPoison::operator=(EffectPoison& other) {
    EffectTurnBasedBased::operator=(other);
    damage = other.damage;
    chance = other.chance;
    return *this;
}
double EffectPoison::getDamage() const {
    return damage;
}

void EffectPoison::setDamage(int damage) {
    this->damage = damage;
}

double EffectPoison::getChance() const {
    return chance;
}

void EffectPoison::setChance(int chance) {
    this->chance = chance;
}

double EffectPoison::apply(Unit* unit) {
    // remainingDuration -= 1;
    return damage; 
}


Effect* EffectPoison::clone() const{
    return new EffectPoison(*this);
}

void EffectPoison::remove(Unit* unit) {}

bool EffectPoison::isThrowable() {
    return true;
}

bool EffectPoison::isPoison() {
    return true;
}