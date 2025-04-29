#include "../include/Potion.hpp"

Potion::Potion(std::string Name, std::string type, std::string rarity, double baseStat, const std::vector<Effect*>& Effects)
        : Item(Name, type, rarity, baseStat, Effects){}

Potion::Potion(const Potion& other) : Item(other) {}

bool Potion::isConsumable() const{
    return true;
}

bool Potion ::isStackAble() const{
    return true;
}