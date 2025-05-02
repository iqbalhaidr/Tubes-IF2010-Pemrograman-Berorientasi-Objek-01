#include "../include/EffectTurnBased.hpp"

EffectTurnBasedBased::EffectTurnBasedBased(const std::string& name, const std::string& description, double duration, double remainingDuration)
    : Effect(name, description, duration, remainingDuration) {}

EffectTurnBasedBased::~EffectTurnBasedBased() {}

EffectTurnBasedBased::EffectTurnBasedBased(const EffectTurnBasedBased& other) 
    : Effect(other) {}

EffectTurnBasedBased& EffectTurnBasedBased::operator=(EffectTurnBasedBased& other) {
    Effect::operator=(other);
    return *this;
}

bool EffectTurnBasedBased::isTurnBased() {
    return true;
}

Effect* EffectTurnBasedBased::clone() const {
    return new EffectTurnBasedBased(*this);
}

double EffectTurnBasedBased::apply(Unit* unit) {
    // remainingDuration -= 1;
    return 0;
}

void EffectTurnBasedBased::remove(Unit* unit) {
}