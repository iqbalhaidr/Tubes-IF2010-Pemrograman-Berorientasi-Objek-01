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
    std::map<std::string, std::vector<Item>> groupedItems;
public:
    Shop(const std::string& directory, const Items& itemMap);

    void buyItem(const std::string& itemName, int quantity, Inventory& inventory);
    void sellItem(const std::string& itemName, int quantity, Inventory& inventory);
    void setPrice(const std::string& itemName, int newPrice);
    void setStock(const std::string& itemName, int newStock);
    void displayDetails(std::string category) const;
    void displayShop() const;
};


#endif