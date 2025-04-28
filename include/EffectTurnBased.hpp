#ifndef EFFECT_TURN_HPP
#define EFFECT_TURN_HPP
#include "effect.hpp"

class EffectTurnBasedBased : public Effect {
    public:
        EffectTurnBasedBased(const std::string& name, const std::string& description, double duration, double remainingDuration);
        ~EffectTurnBasedBased();
        EffectTurnBasedBased(const EffectTurnBasedBased& other);
        EffectTurnBasedBased& operator=(EffectTurnBasedBased& other) = default;

        // Setter Getter

        bool isTurnBased() override;
};


#endif