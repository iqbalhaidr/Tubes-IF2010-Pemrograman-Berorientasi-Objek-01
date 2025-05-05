#include "../include/EffectTurn.hpp"

EffectTurn::EffectTurn(const std::string& name, const std::string& description, double duration, double remainingDuration, int chance, bool isThrowable)
    : Effect(name, description, duration, remainingDuration, chance, isThrowable) {}

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
    // remainingDuration -= 1;
    int randomValue = rand() % 100 + 1;
    if (randomValue > chance) {
        return 1; 
    }
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