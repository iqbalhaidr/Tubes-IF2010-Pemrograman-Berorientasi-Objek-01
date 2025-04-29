#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "item.hpp"

class Weapon :Item
{
private:
    double durability;
public:
    Weapon(std::string name, std::string type, std::string rarity,
        double baseStat,
        const std::vector<Effect*>& effects);
    Weapon(const Weapon& other);
    ~Weapon();
    bool isConsumable() const;
    bool isStackAble() const;
    Item* cloneItem();
};

#endif
