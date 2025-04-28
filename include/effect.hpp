#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <string>
#include "unit.hpp"
class Effect{
    protected:
        std::string name;
        std::string description;
        double duration;
        double remainingDuration;

    public:
        Effect(const std::string& name, const std::string& description, double duration, double remainingDuration);
        ~Effect();
        Effect(const Effect& other);
        Effect& operator=(Effect& other);

        //Setter Getter
        std::string getName() const;   
        std::string getDescription() const;
        double getDuration() const;
        double getRemainingDuration() const;

        void setName(const std::string& name);
        void setDescription(const std::string& description);
        void setDuration(double duration);
        void setRemainingDuration(double remainingDuration);


        virtual double apply(Unit* unit) = 0;
        virtual void remove(Unit* unit);

        virtual Effect* clone() const = 0;

        virtual bool isDamage();
        virtual bool isDefensive();
        virtual bool isTurnBased();
        virtual bool isTurn();
};

#endif