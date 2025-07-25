#include "../include/EffectDamage.hpp"

EffectDamage::EffectDamage(const std::string& name, const std::string& description, double duration, double remainingDuration, int chance, double damage, bool isThrowable)
    : Effect(name, description, duration, remainingDuration, chance, isThrowable), damage(damage) {}

EffectDamage::~EffectDamage() {}

EffectDamage::EffectDamage(const EffectDamage& other) 
    : Effect(other), damage(other.damage) {}

EffectDamage& EffectDamage::operator=(EffectDamage& other) {
    Effect::operator=(other);
    chance = other.chance;
    damage = other.damage;
    return *this;
}

double EffectDamage::getChance() const {
    return chance;
}

double EffectDamage::getDamage() const {
    return damage;
}

void EffectDamage::setChance(double chance) {
    this->chance = chance;
}

void EffectDamage::setDamage(double damage) {
    this->damage = damage;
}

double EffectDamage::apply(Unit* unit) {
    int random = rand() % 100 + 1;
    // remainingDuration -= 1;
    if (random <= chance){
        return damage;
    }

    else{
        return 0;    
    }
}

bool EffectDamage::isDamage(){return true;}

Effect* EffectDamage::clone() const {
    return new EffectDamage(*this);
}

void EffectDamage::remove(Unit* unit) {}