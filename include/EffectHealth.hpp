#include "effect.hpp"

class EffectHealth : public Effect {
    private:
        int healAmount;
    public:
        EffectHealth(const std::string& name, const std::string& description, double duration, double remainingDuration, int healAmount);
        ~EffectHealth();
        EffectHealth(EffectHealth& other);
        EffectHealth& operator=(EffectHealth& other) = default;

        // Setter Getter
        int getHealAmount() const;
        void setHealAmount(int healAmount);

        void apply(Unit* unit) override;
        void remove(Unit unit) override;
}