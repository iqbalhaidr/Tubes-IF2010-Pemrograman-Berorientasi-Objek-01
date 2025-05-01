#include "../include/EffectTurn.hpp"

EffectTurn::EffectTurn(const std::string& name, const std::string& description, double duration, double remainingDuration, int chance)
    : Effect(name, description, duration, remainingDuration), chance(chance) {}

EffectTurn::~EffectTurn() {}

EffectTurn::EffectTurn(const EffectTurn& other) 
    : Effect(other) {}

EffectTurn& EffectTurn::operator=(EffectTurn& other) {
    Effect::operator=(other);
    return *this;
}

bool EffectTurn::isTurn() {
    return true;
}

double EffectTurn::apply(Unit* unit) {
    // Default implementation does nothing
    remainingDuration -= 1;
    return 0;
}

Effect* EffectTurn::clone() const {
    return new EffectTurn(*this);
}

int EffectTurn::getChance() const {
    return chance;
}

void EffectTurn::setChance(int chance) {
    this->chance = chance;
}