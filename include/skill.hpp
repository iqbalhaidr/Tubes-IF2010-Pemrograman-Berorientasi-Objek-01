#ifndef SKILL_HPP
#define SKILL_HPP

#include <iostream>
#include <string>
class Skill{
    private:
        std::string name;
        float manaCost;
        float masterCost;
        float effectChance;
        std::string effecType;
    public:
        Skill(const std::string& name, float manaCost, float masterCost, float effectChance, const std::string& effectType);
        ~Skill();
        Skill(Skill&& other);
        Skill& operator=(Skill&& other) = default;


    //Setter Getter
        std::string getName() const;
        float getManaCost() const;
        float getMasterCost() const;
        float getEffectChance() const;

        std::string getEffectType() const;
        void setName(const std::string& name);
        void setManaCost(float manaCost);
        void setMasterCost(float masterCost);
        void setEffectChance(float effectChance);
        void setEffectType(const std::string& effectType);    
};

#endif