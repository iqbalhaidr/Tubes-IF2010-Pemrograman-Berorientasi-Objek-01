#include "../include/Pendant.hpp"

Pendant::Pendant(std::string Name, std::string type, std::string rarity, double baseStat, const std::vector<Effect*>& Effects)
        : Item(Name, type, rarity, baseStat, Effects){}

Pendant::Pendant(const Pendant& other) : Item(other) {}

bool Pendant::isConsumable() const{
    return false;
}

bool Pendant ::isStackAble() const{
    return true;
}