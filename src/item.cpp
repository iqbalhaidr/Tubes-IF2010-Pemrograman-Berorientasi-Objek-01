#include "../include/item.hpp"

Item::Item(std::string Name, std::string type, std::string rarity, double baseStat, const std::vector<Effect*>& Effects){
    this->name = name;
    this->type = type;
    this->rarity = rarity;
    this->baseStat = baseStat;
    for(size_t i =0; i< Effects.size(); i++){
        effects.push_back(Effects[i]->clone());
    }

}

Item::~Item() {
    for(size_t i =0; i< effects.size(); i++){
        delete effects[i];
    }
}

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

std::vector<Effect*> Item::getEffects() const {
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

double Item :: getFinalStat() const {
    return baseStat * getStatMultiplier(); 
}


