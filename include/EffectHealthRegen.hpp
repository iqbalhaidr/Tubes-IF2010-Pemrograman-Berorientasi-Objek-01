#ifndef HEALTHREGEN_HPP
#define HEALTHREGEN_HPP
#include "EffectTurnBased.hpp"

class EffectHealthRegen : public EffectTurnBasedBased {
    private:
        int healAmount;
    public:
        EffectHealthRegen(const std::string& name, const std::string& description, double duration, double remainingDuration, int healAmount);
        ~EffectHealthRegen();
        EffectHealthRegen(const EffectHealthRegen& other);
        EffectHealthRegen& operator=(EffectHealthRegen& other) ;

        // Setter Getter
        int getHealAmount() const;
        void setHealAmount(int healAmount);

        double apply(Unit* unit) override;
        void remove(Unit* unit) override;
        Effect* clone() const override;
        bool isHealthRegen() override;
};


#endif