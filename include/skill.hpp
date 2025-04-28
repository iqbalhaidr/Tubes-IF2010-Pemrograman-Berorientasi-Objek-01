#ifndef SKILL_HPP
#define SKILL_HPP

#include <iostream>
#include <string>
#include "Effect.hpp"   
class Skill{
    private:
        std::string name;
        double manaCost;
        double masterCost;
        double effectChance;
        double damage;
    public:
        vector<Effect*> effects;
        Skill(const std::string& name, double manaCost, double masterCost, double effectChance, vector<Effect*> effects);
        ~Skill();
        Skill(Skill& other);
        Skill& operator=(Skill& other) = default;


    //Setter Getter
        std::string getName() const;
        double getManaCost() const;
        double getMasterCost() const;
        double getEffectChance() const;
        double getDamage() const;

        std::string getEffectType() const;
        void setName(const std::string& name);
        void setManaCost(double manaCost);
        void setMasterCost(double masterCost);
        void setEffectChance(double effectChance);
        void setEffectType(const std::string& effectType);    
        void setDamage(double damage);
        vector<Effect*> getEffects() const;
};

#endif