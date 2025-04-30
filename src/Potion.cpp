#include "../include/Potion.hpp"

Potion::Potion(std::string itemId, std::string Name, std::string type, std::string rarity, double baseStat, const std::vector<Effect*>& Effects)
        : Item(itemId, Name, type, rarity, baseStat, Effects){}

Potion::Potion(const Potion& other) : Item(other) {}
Potion::~Potion(){};

bool Potion::isConsumable() const{
    return true;
}

bool Potion ::isStackAble() const{
    return true;
}

Item* Potion::cloneItem(){
    return new Potion(*this);
}