#ifndef ARMOR_HPP
#define ARMOR_HPP

#include "item.hpp"

class Armor : public Item
{
private:
    double durability;
public:
    Armor(std::string itemID, std::string name, std::string type, std::string rarity,
        double baseStat,
        const std::vector<Effect*>& effects);
    Armor(const Armor& other);
    ~Armor();
    bool isConsumable() const;
    bool isStackable() const;
    Item* cloneItem();
};



#endif
