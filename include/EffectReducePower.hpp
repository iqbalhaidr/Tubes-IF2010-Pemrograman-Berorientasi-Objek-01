#ifndef EFFECTREDUCEPOWER_HPP
#define EFFECTREDUCEPOWER_HPP
#include "Effect.hpp"

class EffectReducePower : public Effect {
    private:
        double amount;
        double chance;
    public:
        EffectReducePower(const std::string& name, const std::string& description, double duration, double remainingDuration, double chance, double amount);
        ~EffectReducePower();
        EffectReducePower(const EffectReducePower& other);
        EffectReducePower& operator=(EffectReducePower& other);

        // Setter Getter
        double getamount() const;
        void setamount(double amount);
        double getChance() const;
        void setChance(double chance);

        
        double apply(Unit* unit) override;
        void remove(Unit* unit) override;
        bool isReducePower() override;
};

#endif