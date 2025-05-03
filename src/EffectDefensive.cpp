#include "../include/EffectDefensive.hpp"

EffectDefensive::EffectDefensive(const std::string& name, const std::string& description, double duration, double remainingDuration, int chance, int armorAmount, int magicResistAmount)
    : Effect(name, description, duration, remainingDuration), chance(chance), defense(defense) {}

EffectDefensive::~EffectDefensive() {}

EffectDefensive::EffectDefensive(const EffectDefensive& other) 
    : Effect(other), chance(other.chance), defense(other.defense) {}

EffectDefensive& EffectDefensive::operator=(EffectDefensive& other) {
    Effect::operator=(other);
    chance = other.chance;
    defense = other.defense;
    return *this;
}

double EffectDefensive::getChance() const {
    return chance;
}

double EffectDefensive::getDefense() const {
    return defense;
}   

void EffectDefensive::setChance(double chance) {
    this->chance = chance;
}   

void EffectDefensive::setDefense(double defense) {
    this->defense = defense;
}

double EffectDefensive::apply(Unit* unit) {
    int random = rand() % 100 + 1;
    // remainingDuration -= 1;
    if (random <= chance){
        return defense;
    }

    else{
        return 0;    
    }
}

bool EffectDefensive::isDefensive(){return true;}

Effect* EffectDefensive::clone() const {
    return new EffectDefensive(*this);
}

void EffectDefensive::remove(Unit* unit) {}