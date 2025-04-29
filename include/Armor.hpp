#ifndef ARMOR_HPP
#define ARMOR_HPP

#include "item.hpp"

class Armor : Item
{
private:
    double durability;
public:
    Armor(std::string name, std::string type, std::string rarity,
        double baseStat,
        const std::vector<Effect*>& effects);
    Armor(const Armor& other);
    ~Armor();
    bool isConsumable() const;
    bool isStackAble() const;
    Item* cloneItem();
};



#endif
