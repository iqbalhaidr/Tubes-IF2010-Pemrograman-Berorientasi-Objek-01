#ifndef EFFECTDEFENSIVE_HPP
#define EFFECTDEFENSIVE_HPP

#include "effect.hpp"

class EffectDefensive : public Effect {
    private:
        double defense;
    public:
        EffectDefensive(const std::string& name, const std::string& description, double duration, double remainingDuration, int chance, int armorAmount, int magicResistAmount, bool isThrowable);
        ~EffectDefensive();
        EffectDefensive(const EffectDefensive& other);
        EffectDefensive& operator=(EffectDefensive& other);

        // Setter Getter
        double getChance() const;
        double getDefense() const;
        void setChance(double chance);
        void setDefense(double defense);

        double apply(Unit* unit) override;
        void remove(Unit* unit) override;
        Effect* clone() const override;
        bool isDefensive();
};

#endif
