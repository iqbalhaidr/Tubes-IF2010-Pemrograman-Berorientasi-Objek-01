    #ifndef EFFECT_TURN_HPP
    #define EFFECT_TURN_HPP
    #include "effect.hpp"

    class EffectTurnBasedBased : public Effect {
        public:
            EffectTurnBasedBased(const std::string& name, const std::string& description, double duration, double remainingDuration, int chance, bool isThrowable);
            ~EffectTurnBasedBased();
            EffectTurnBasedBased(const EffectTurnBasedBased& other);
            EffectTurnBasedBased& operator=(EffectTurnBasedBased& other);

            // Setter Getter

            bool isTurnBased() override;
            virtual Effect* clone() const override;
            double apply(Unit* unit) override;
            void remove(Unit* unit) override;

    };


    #endif