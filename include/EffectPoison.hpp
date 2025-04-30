#ifndef EffectPoison_HPP
#define EffectPoison_HPP
#include "EffectTurnBased.hpp"

class EffectPoison : public EffectTurnBasedBased {
    private:
        double damage;
        double chance;
    public:
        EffectPoison(const std::string& name, const std::string& description, double duration, double remainingDuration, double chance, double damage);
        ~EffectPoison();
        EffectPoison(const EffectPoison& other);
        EffectPoison& operator=(EffectPoison& other);

        // Setter Getter
        double getDamage() const;
        double setDamage(int damage);
        double getChance() const;
        double setChance(int chance);

        
        double apply(Unit* unit) override;
        Effect* clone() const override;
        void remove(Unit* unit) override;
        bool isThrowable() override;
        bool isPoison() override;
};


#endif