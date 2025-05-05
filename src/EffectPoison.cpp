#include "../include/EffectPoison.hpp"

EffectPoison::EffectPoison(const std::string& name, const std::string& description, double duration, double remainingDuration, int chance, double damage, bool isThrowable)
    : EffectTurnBasedBased(name, description, duration, remainingDuration, chance, isThrowable), damage(damage) {}
EffectPoison::~EffectPoison() {}
EffectPoison::EffectPoison(const EffectPoison& other) 
    : EffectTurnBasedBased(other), damage(other.damage) {}
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
    int randomValue = rand() % 100 + 1;
    if (randomValue > chance) {
        return damage;   
    }
    return 0;
}


Effect* EffectPoison::clone() const{
    return new EffectPoison(*this);
}

void EffectPoison::remove(Unit* unit) {}


bool EffectPoison::isPoison() {
    return true;
}