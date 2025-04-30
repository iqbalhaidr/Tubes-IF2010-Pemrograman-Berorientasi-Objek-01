#ifndef POTION_HPP
#define POTION_HPP

#include "item.hpp"

class Potion : Item
{
private:
    double durability;
public:
    Potion(std::string name, std::string type, std::string rarity,
        double baseStat,
        const std::vector<Effect*>& effects);
    Potion(const Potion& other);
    ~Potion();
    bool isConsumable() const;
    bool isStackAble() const;
    Item* cloneItem();
};
#endif
