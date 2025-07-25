#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "item.hpp"

class Weapon :public Item
{
private:
    double durability;
public:
    Weapon(std::string itemId ,std::string name, std::string type, std::string rarity,
        double baseStat,
        const std::vector<Effect*>& effects);
    Weapon(const Weapon& other);
    ~Weapon();
    bool isConsumable() const;
    bool isStackable() const;
    Item* cloneItem();
};

#endif
