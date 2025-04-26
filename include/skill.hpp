#ifndef SKILL_HPP
#define SKILL_HPP

#include <iostream>
#include <string>
class Skill{
    private:
        std::string name;
        double manaCost;
        double masterCost;
        double effectChance;
        std::string effecType;
    public:
        Skill(const std::string& name, double manaCost, double masterCost, double effectChance, const std::string& effectType);
        ~Skill();
        Skill(Skill& other);
        Skill& operator=(Skill& other) = default;


    //Setter Getter
        std::string getName() const;
        double getManaCost() const;
        double getMasterCost() const;
        double getEffectChance() const;

        std::string getEffectType() const;
        void setName(const std::string& name);
        void setManaCost(double manaCost);
        void setMasterCost(double masterCost);
        void setEffectChance(double effectChance);
        void setEffectType(const std::string& effectType);    
};

#endif