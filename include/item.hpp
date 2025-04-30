#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>
#include "EffectInclude.hpp"

class Item {
    private:
        std::string itemId;
        std::string name;
        std::string type;
        std::string rarity;
        double baseStat;
        std::vector<Effect*> effects;
    
    public:
        Item(std::string itemId, std::string name, std::string type, std::string rarity, double baseStat,const std::vector<Effect*>& effects);
        Item(const Item& other);
        ~Item();

        bool operator==(const Item& other);
    
        std::string getId(){return itemId;};
        std::string getName() const;
        std::string getItemType() const;
        std::string getRarity() const;
        double getBaseStat() const;
        std::vector<Effect*> getEffects() const;
        double getStatMultiplier() const;
        double getFinalStat() const;
        void scaleItemEffect() ;
        virtual bool isConsumable() const {return false;};
        virtual bool isStackable() const {return true;};
        virtual Item* cloneItem() = 0;

    };


#endif
