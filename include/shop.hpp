#ifndef SHOP_HPP
#define SHOP_HPP

#include "items.hpp"
#include "inventory.hpp"
#include <sstream>
#include <fstream>
#include <map>
#include <string> 
#include <filesystem> 

namespace fs = std::filesystem; 

class Shop
{
private:
    std::map<std::string, std::pair<int,int>> availableItems;
    std::map<std::string, std::vector<Item>> groupedItems; // Configuration file for shop items
    std::map<std::string, std::pair<int,int>> shopConfig;
public:
    Shop(const std::string& directory, Items& itemMap);
    void saveShop(const std::string& directory, Items& itemMap) ;
    void buyItem(const std::string& itemName, int quantity, Inventory& inventory);
    void sellItem(const std::string& itemName, int quantity, Inventory& inventory);
    void restock();
    void setStock(const std::string& itemName, int stock);
    void displayDetails(std::string itemName) const;
    void displayShop() const;
};


#endif