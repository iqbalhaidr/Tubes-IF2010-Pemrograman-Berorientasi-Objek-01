#ifndef POTION_HPP
#define POTION_HPP

#include "item.hpp"

class Potion : public Item
{
private:
    double durability;
public:
    Potion(std::string itemId, std::string name, std::string type, std::string rarity,
        double baseStat,
        const std::vector<Effect*>& effects);
    Potion(const Potion& other);
    ~Potion();
    bool isConsumable() const;
    bool isStackAble() const;
    Item* cloneItem();
};
#endif
