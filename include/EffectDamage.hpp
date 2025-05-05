#ifndef EFFECTDAMAGE_HPP
#define EFFECTDAMAGE_HPP
#include "effect.hpp"

class EffectDamage : public Effect {
    private:
        double damage;

    public:
        EffectDamage(const std::string& name, const std::string& description, double duration, double remainingDuration, int chance, double damage, bool isThrowable);
        ~EffectDamage();
        EffectDamage(const EffectDamage& other);
        EffectDamage& operator=(EffectDamage& other);

        // Setter Getter
        double getChance() const;
        double getDamage() const;
        void setChance(double chance);
        void setDamage(double damage);

        double apply(Unit* unit) override;
        void remove(Unit* unit) override;

        Effect* clone() const override;
        bool isDamage();
};
#endif