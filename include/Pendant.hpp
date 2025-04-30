#ifndef PENDANT_HPP
#define PENDANT_HPP

#include "item.hpp"

class Pendant : public Item
{
private:
    double durability;
public:
    Pendant(std::string itemId, std::string name, std::string type, std::string rarity,
        double baseStat,
        const std::vector<Effect*>& effects);
    Pendant(const Pendant& other);
    ~Pendant();
    bool isConsumable() const;
    bool isStackAble() const;
    Item* cloneItem();
};

#endif
