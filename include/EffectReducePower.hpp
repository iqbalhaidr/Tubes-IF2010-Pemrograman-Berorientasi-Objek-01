#ifndef EFFECTREDUCEPOWER_HPP
#define EFFECTREDUCEPOWER_HPP
#include "Effect.hpp"

class EffectReducePower : public Effect {
    private:
        double damage;
        double chance;
    public:
        EffectReducePower(const std::string& name, const std::string& description, double duration, double remainingDuration, double chance, double damage);
        ~EffectReducePower();
        EffectReducePower(const EffectReducePower& other);
        EffectReducePower& operator=(EffectReducePower& other);

        // Setter Getter
        double getDamage() const;
        void setDamage(double damage);
        double getChance() const;
        void setChance(double chance);

        
        double apply(Unit* unit) override;
        void remove(Unit* unit) override;
        bool isReducePower() override;
};

#endif