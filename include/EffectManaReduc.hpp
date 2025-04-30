#ifndef EFFECTMANAREDUC_HPP
#define EFFECTMANAREDUC_HPP
#include "EffectTurnBased.hpp"


class EffectManaReduc : public EffectTurnBasedBased{
    private:
        double manaAmount;

    public:
        EffectManaReduc(const std::string& name, const std::string& description, double duration, double remainingDuration, double manaAmount);
        ~EffectManaReduc();
        EffectManaReduc(const EffectManaReduc& other);
        EffectManaReduc& operator=(EffectManaReduc& other) ;

        double getManaAmount() const;
        void setManaAmount(int manaAmount);

        double apply(Unit* unit) override;
        void remove(Unit* unit) override;
        bool isManaReduc() override;

        
};


#endif