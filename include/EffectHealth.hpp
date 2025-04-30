#ifndef EFFECTHEALTH_HPP
#define EFFECTHEALTH_HPP
#include "effect.hpp"

class EffectHealth : public Effect {
    private:
        int  healAmount;
        double chance;
    public:
        EffectHealth(const std::string& name, const std::string& description, double duration, double remainingDuration, double chance, int healAmount);
        ~EffectHealth();
        EffectHealth(const EffectHealth& other);
        EffectHealth& operator=(EffectHealth& other);

        // Setter Getter
        int getHealAmount() const;
        void setHealAmount(int healAmount);
        double getChance() const;
        void setChance(double chance);

        double apply(Unit* unit) override;
        Effect* clone() const override;
        bool isHealth() override;
};

#endif