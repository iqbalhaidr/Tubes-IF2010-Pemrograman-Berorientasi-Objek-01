#ifndef EFFECTTURN_HPP
#define EFFECTTURN_HPP
#include "effect.hpp"

class EffectTurn: public Effect {
    public:
        EffectTurn(const std::string& name, const std::string& description, double duration, double remainingDuration);
        ~EffectTurn();
        EffectTurn(EffectTurn& other);
        EffectTurn& operator=(EffectTurn& other) = default;

        // Setter Getter
        double apply(Unit* unit) override;
        bool isTurn() override;
};


#endif