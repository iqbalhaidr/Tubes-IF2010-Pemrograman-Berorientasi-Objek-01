#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "matrix.hpp"
#include "item.hpp"
#include "items.hpp"
#include <map>
#include <string>
#include <utility>
#include <climits>

#define MAX_ITEM 64

class Character;

class Inventory {
private:
    Matrix<std::pair<Item*, int>> backpack;
    std::map<std::string, Item*> equipped;

public:
    static std::string centerText(const std::string &text, int width);
    static Inventory loadInventory(const std::string& directory, const Items& itemMap);
    Inventory(const Matrix<std::pair<Item*, int>>& backp, const std::map<std::string, Item*>& equippedItem);
    
    void saveInventory(const std::string& directory);
    void addItem(std::pair<Item*, int>& value);
    void reduceItem(const Item* item, int amount);
    void useItem(const std::string itemID, Character& orang, const Items& itemMap, Unit& target);
    void unequipItem(Character& orang, const std::string& slot, Unit& target);
    void equipItem(std::string slot, Character& orang, Item* item, Unit& target);
    std:: pair<int,int>  getIdxItembyId(const std::string& itemId) const;

    Matrix<std::pair<Item*, int>> getBackpack(){return backpack;};
    Item* getEquippedItem(const std::string& slot){return equipped[slot];};
    std::pair<Item *, int> getItemById(const std::string& itemId);
    std::pair<Item *, int> getItemBackpackByName(const std::string& itemName);
    std::string getEquippedItemId(const std::string& slot) const;
    void setEquipped(const std::string& slot, Item* item);
    void displayBackpack();
    void displayEquipment();
    int getItemQtyInInvent(const std::string& itemName);
    void displayBackpackDetails();

};

#endif
