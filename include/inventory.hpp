#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "matrix.hpp"
#include "items.hpp"
#include <map>
#include <string>
#include <utility>

#define MAX_ITEM 64

class Inventory {
private:
    Matrix<std::pair<std::string, int>> backpack;
    std::map<std::string, std::string> equipped;

public:
    Inventory(const std::string& directory, const Items& itemMap);
    
    void saveInventory(const std::string& directory);
    void addItem(std::pair<const std::string, int>& value);
    void reduceItem(const std::string& itemName, int amount);
    void setEquippedItem(const std::string& slot, const std::string& item);
    Item* getEquippedItem(const std::string& slot) const;

    Matrix<std::pair<std::string, int>> getBackpack();
};

#endif
