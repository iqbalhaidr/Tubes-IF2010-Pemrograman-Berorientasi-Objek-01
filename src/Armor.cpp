#include "../include/Armor.hpp"

Armor::Armor(std::string itemId, std::string Name, std::string type, std::string rarity, double baseStat, const std::vector<Effect*>& Effects)
        : Item(itemId, Name, type, rarity, baseStat, Effects){}

Armor::Armor(const Armor& other) : Item(other) {}
Armor::~Armor(){};

bool Armor::isConsumable() const{
    return false;
}

bool Armor ::isStackable() const{
    return false;
}

Item* Armor::cloneItem(){
    return new Armor(*this);
}