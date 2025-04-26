#ifndef EFFECTDAMAGE_HPP
#define EFFECTDAMAGE_HPP
#include "effect.hpp"

class EffectDamage : public Effect {
    private:
        int chance;
        double damage;

    public:
        EffectDamage(const std::string& name, const std::string& description, double duration, double remainingDuration, int chance, double damage);
        ~EffectDamage();
        EffectDamage(EffectDamage& other);
        EffectDamage& operator=(EffectDamage& other) = default;

        // Setter Getter
        double getChance() const;
        double getDamage() const;
        void setChance(double chance);
        void setDamage(double damage);

        void apply(Unit* unit) override;
        void remove(Unit unit) override;
};

#endif