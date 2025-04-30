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
    std::map<std::string, Item*> equipped;

public:
    static Inventory loadInventory(const std::string& directory, const Items& itemMap);
    Inventory(const Matrix<std::pair<Item*, int>>& backp, const std::map<std::string, Item*>& equippedItem);
    
    void saveInventory(const std::string& directory);
    void addItem(std::pair<Item*, int>& value);
    void reduceItem(const Item* item, int amount);
    void useItem(const std::string itemID, Character& orang, const Items& itemMap);
    void unequipItem(Character& orang,const std::string& slot);
    void generalUnequip(std::string slot, Character& orang);
    void generalEquip(std::string slot, Character& orang, Item* item);
    std:: pair<int,int>  getIdxItembyId(const std::string& itemId) const;

    Item* getEquippedItem(const std::string& slot){return equipped[slot];};
    std::string getEquippedItemId(const std::string& slot) const;
};

#endif
