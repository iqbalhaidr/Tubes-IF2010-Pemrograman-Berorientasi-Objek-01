#ifndef EFFECTHEALTH_HPP
#define EFFECTHEALTH_HPP
#include "effect.hpp"

class EffectHealth : public Effect {
    private:
        int  healAmount;
        int baseHealAmount;
    public:
        EffectHealth(const std::string& name, const std::string& description, double duration, double remainingDuration, int chance, int healAmount, bool isThrowable);
        ~EffectHealth();
        EffectHealth(const EffectHealth& other);
        EffectHealth& operator=(EffectHealth& other);

        // Setter Getter
        int getHealAmount() const;
        void setHealAmount(int healAmount);
        double getChance() const;
        void setChance(double chance);

        double apply(Unit* unit) override;
        void remove(Unit* unit) override;
        Effect* clone() const override;
        bool isHealth() override;
};

#endif