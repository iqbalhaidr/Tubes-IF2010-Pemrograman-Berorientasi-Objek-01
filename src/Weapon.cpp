#include "../include/Weapon.hpp"

Weapon::Weapon(std::string itemId, std::string Name, std::string type, std::string rarity, double baseStat, const std::vector<Effect*>& Effects)
        : Item(itemId, Name, type, rarity, baseStat, Effects){}

Weapon::Weapon(const Weapon& other) : Item(other) {}

Weapon::~Weapon(){};

bool Weapon::isConsumable() const{
    return false;
}

bool Weapon ::isStackAble() const{
    return false;
}

Item* Weapon::cloneItem(){
    return new Weapon(*this);
}