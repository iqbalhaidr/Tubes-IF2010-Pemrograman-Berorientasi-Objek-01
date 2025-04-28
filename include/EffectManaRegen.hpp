#ifndef EFFECTMANAREGEN_HPP
#define EFFECTMANAREGEN_HPP
#include "EffectTurnBased.hpp"

class EffectManaRegen : public EffectTurnBasedBased {
    private:
        int manaAmount;
    public:
        EffectManaRegen(const std::string& name, const std::string& description, double duration, double remainingDuration, int manaAmount);
        ~EffectManaRegen();
        EffectManaRegen(const EffectManaRegen& other);
        EffectManaRegen& operator=(EffectManaRegen& other) = default;

        // Setter Getter
        int getManaAmount() const;
        void setManaAmount(int manaAmount);

        double apply(Unit* unit) override;
        Effect* clone() const override;
        void remove(Unit* unit) override;
};


#endif