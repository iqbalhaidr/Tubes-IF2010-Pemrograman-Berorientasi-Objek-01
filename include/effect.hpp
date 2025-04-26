#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <string>
#include "unit.hpp"
class Effect{
    private:
        std::string name;
        std::string description;
        double duration;
        double remainingDuration;

    public:
        Effect(const std::string& name, const std::string& description, double duration, double remainingDuration);
        ~Effect();
        Effect(Effect& other);
        Effect& operator=(Effect& other);

        //Setter Getter
        std::string getName() const;   
        std::string getDescription() const;
        double getDuration() const;
        double getRemainingDuration() const;


        virtual void apply(Unit unit) = 0;
        virtual void remove(Unit unit) = 0;
};

#endif