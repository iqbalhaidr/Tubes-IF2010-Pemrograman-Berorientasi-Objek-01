#ifndef EFFECTTURN_HPP
#define EFFECTTURN_HPP
#include "effect.hpp"

class EffectTurn: public Effect {
    private:
    public:
        EffectTurn(const std::string& name, const std::string& description, double duration, double remainingDuration, int chance, bool isThrowable);
        ~EffectTurn();
        EffectTurn(const EffectTurn& other);
        EffectTurn& operator=(EffectTurn& other);

        // Setter Getter
        int getChance() const;
        void setChance(int chance);
        double apply(Unit* unit) override;
        Effect* clone() const override;
        bool isTurn() override;
};


#endif