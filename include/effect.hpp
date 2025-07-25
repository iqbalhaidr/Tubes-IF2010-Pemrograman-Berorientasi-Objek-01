#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <string>

class Unit; // Forward declaration

class Effect{
    protected:
        std::string name;
        std::string description;
        double duration;
        double remainingDuration;
        int chance;
        bool lempar;

    public:
        Effect(const std::string& name, const std::string& description, double duration, double remainingDuration, int chance = 100, bool isThrowable = false);
        ~Effect();
        Effect(const Effect& other);
        Effect& operator=(Effect& other);
        static Effect* createEffect(const std::string& name);
        bool operator==(const Effect& other) const;
            //Setter Getter
        std::string getName() const;   
        std::string getDescription() const;
        double getDuration() const;
        double getRemainingDuration() const;
        int getChance();

        void setName(const std::string& name);
        void setDescription(const std::string& description);
        void setDuration(double duration);
        void setRemainingDuration(double remainingDuration);
        void setChance(int chance);


        virtual double apply(Unit* unit) = 0;
        virtual void remove(Unit* unit);

        virtual Effect* clone() const = 0;

        virtual bool isDamage();
        virtual bool isDefensive();
        virtual bool isTurnBased();
        virtual bool isTurn();
        virtual bool isHealthRegen();
        virtual bool isManaRegen();
        bool isThrowable();
        virtual bool isPoison();
        virtual bool isHealth();
        virtual bool isManaReduc();
        virtual bool isReducePower();

        void decreaseRemainingDuration();
};

#endif