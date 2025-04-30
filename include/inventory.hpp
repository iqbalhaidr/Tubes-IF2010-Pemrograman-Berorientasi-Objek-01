#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "matrix.hpp"
#include "item.hpp"
#include "items.hpp"
#include "character.hpp"
#include <map>
#include <string>
#include <utility>

#define MAX_ITEM 64

class Inventory {
private:
    Matrix<std::pair<Item*, int>> backpack;
    std::map<std::string, std::string> equipped;

public:
    static Inventory loadInventory(const std::string& directory, const Items& itemMap);
    Inventory(const Matrix<std::pair<Item*, int>>& backp, const std::map<std::string, std::string>& equippedItem);
    
    void saveInventory(const std::string& directory);
    void addItem(std::pair<Item*, int>& value);
    void reduceItem(const Item* item, int amount);
    void setEquippedItem(const std::string& slot, const std::string& item, const Character& orang);
    Item* getEquippedItem(const std::string& slot) const;

    std::string getEquippedItemId(const std::string& slot) const;
};

#endif
