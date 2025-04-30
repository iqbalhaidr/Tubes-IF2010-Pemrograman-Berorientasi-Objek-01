#ifndef SKILL_HPP
#define SKILL_HPP

#include <iostream>
#include <string>
#include "effect.hpp"   
#include <vector>
using namespace std;
class Skill{
    private:
        std::string name;
        double manaCost;
        double masterCost;
        double skillChance;
        double damage;
    public:
        vector<Effect*> effects;
        Skill(const std::string& name, double manaCost, double masterCost, double skillChance, double damage, vector<Effect*> effects);
        ~Skill();
        Skill(Skill& other);
        Skill& operator=(Skill& other) = default;


    //Setter Getter
        std::string getName() const;
        double getManaCost() const;
        double getMasterCost() const;
        double getskillChance() const;
        double getDamage() const;
        vector<Effect*> getEffects() const;
        
        // std::string getEffectType() const;
        void setName(const std::string& name);
        void setManaCost(double manaCost);
        void setMasterCost(double masterCost);
        void setskillChance(double skillChance);
        // void setEffectType(const std::string& effectType);    
        void setDamage(double damage);
        void setEffects(vector<Effect*> effects);
};

#endif