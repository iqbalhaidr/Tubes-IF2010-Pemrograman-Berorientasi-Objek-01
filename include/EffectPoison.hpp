#ifndef EffectPoison_HPP
#define EffectPoison_HPP
#include "EffectTurnBased.hpp"

class EffectPoison : public EffectTurnBasedBased {
    private:
        double damage;
    public:
        EffectPoison(const std::string& name, const std::string& description, double duration, double remainingDuration, int chance, double damage, bool isThrowable);
        ~EffectPoison();
        EffectPoison(const EffectPoison& other);
        EffectPoison& operator=(EffectPoison& other);

        // Setter Getter
        double getDamage() const;
        void setDamage(int damage);
        double getChance() const;
        void setChance(int chance);

        
        double apply(Unit* unit) override;
        Effect* clone() const override;
        void remove(Unit* unit) override;
        bool isPoison() override;
};


#endif