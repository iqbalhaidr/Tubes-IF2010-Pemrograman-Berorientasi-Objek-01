#include "../include/Pendant.hpp"

Pendant::Pendant(std::string itemId, std::string Name, std::string type, std::string rarity, double baseStat, const std::vector<Effect*>& Effects)
        : Item(itemId,Name, type, rarity, baseStat, Effects){}

Pendant::Pendant(const Pendant& other) : Item(other) {}
Pendant::~Pendant(){};

bool Pendant::isConsumable() const{
    return false;
}

bool Pendant ::isStackable() const{
    return true;
}

Item* Pendant::cloneItem(){
    return new Pendant(*this);
}