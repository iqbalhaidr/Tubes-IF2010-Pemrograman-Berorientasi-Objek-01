#include "effect.hpp"

class EffectDefensive : public Effect {
    private:
        int chance;
        double defense;
    public:
        EffectDefensive(const std::string& name, const std::string& description, double duration, double remainingDuration, int armorAmount, int magicResistAmount);
        ~EffectDefensive();
        EffectDefensive(EffectDefensive& other);
        EffectDefensive& operator=(EffectDefensive& other) = default;

        // Setter Getter
        double getChance() const;
        double getDefense() const;
        void setChance(double chance);
        void setDefense(double defense);

        double apply(Unit* unit) override;
        void remove(Unit* unit) override;
        bool isDefensive();
};