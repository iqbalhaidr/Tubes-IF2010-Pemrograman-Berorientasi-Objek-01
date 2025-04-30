#include "../include/Armor.hpp"

Armor::Armor(std::string Name, std::string type, std::string rarity, double baseStat, const std::vector<Effect*>& Effects)
        : Item(Name, type, rarity, baseStat, Effects){}

Armor::Armor(const Armor& other) : Item(other) {}

bool Armor::isConsumable() const{
    return false;
}

bool Armor ::isStackAble() const{
    return false;
}

Item* Armor::cloneItem(){
    return new Armor(*this);
}