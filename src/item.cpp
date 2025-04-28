#include "../include/item.hpp"

Item::Item(std::string name, std::string type, std::string rarity,
           double baseStat,
           const std::vector<std::string>& effects)
    : name(name), type(type), rarity(rarity),
     baseStat(baseStat), effects(effects) {}

Item::~Item() {}

std::string Item::getName() const{
    return name;
}

std::string Item::getItemType() const{
    return type;
}

std::string Item::getRarity() const{
    return rarity;
}


double Item::getBaseStat() const{
    return baseStat;
}

std::vector<std::string> Item::getEffects() {
    return effects;
}

double Item :: getStatMultiplier() const {
    if (rarity == "E") return 1.0;
    if (rarity == "D") return 1.2;
    if (rarity == "C") return 1.5;
    if (rarity == "B") return 2.0;
    if (rarity == "A") return 3.0;
    if (rarity == "S") return 6.0;
    return 1.0; 
}

// double Item :: getFinalStat() const {
//     return baseStat * getStatMultiplier() * (1 + (level * 0.05)); 
// }
