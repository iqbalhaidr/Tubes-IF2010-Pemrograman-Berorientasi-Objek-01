#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>
#include "EffectInclude.hpp"

class Item {
    private:
        std::string name;
        std::string type;
        std::string rarity;
        double baseStat;
        std::vector<Effect*> effects;
    
    public:
        Item(std::string name, std::string type, std::string rarity,
             double baseStat,
             const std::vector<Effect*>& effects);
    
        ~Item();
    
        std::string getName() const;
        std::string getItemType() const;
        std::string getRarity() const;
        double getBaseStat() const;
        std::vector<Effect*> getEffects() const;
        double getStatMultiplier() const;
        double getFinalStat() const;
        virtual bool isConsumable() const {return false;};
    };


#endif
