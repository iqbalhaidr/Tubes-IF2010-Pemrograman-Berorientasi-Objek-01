#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <string>
#include "unit.hpp"
class Effect{
    private:
        std::string name;
        std::string description;
        float duration;
        float remainingDuration;

    public:
        Effect(const std::string& name, const std::string& description, float duration, float remainingDuration);
        ~Effect();
        Effect(Effect& other);
        Effect& operator=(Effect&& other);

        //Setter Getter
        virtual void apply(Unit unit) = 0;
        virtual void remove(Unit unit) = 0;
};

#endif