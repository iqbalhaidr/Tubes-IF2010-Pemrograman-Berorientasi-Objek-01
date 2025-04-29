#ifndef EFFECTTURN_HPP
#define EFFECTTURN_HPP
#include "effect.hpp"

class EffectTurn: public Effect {
    private:
        int chance;
    public:
        EffectTurn(const std::string& name, const std::string& description, double duration, double remainingDuration, int chance);
        ~EffectTurn();
        EffectTurn(const EffectTurn& other);
        EffectTurn& operator=(EffectTurn& other) = default;

        // Setter Getter
        double apply(Unit* unit) override;
        Effect* clone() const override;
        bool isTurn() override;
};


#endif