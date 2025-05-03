#ifndef SHOP_HPP
#define SHOP_HPP

#include "items.hpp"
#include "inventory.hpp"
#include "exception.hpp"
#include <sstream>
#include <fstream>
#include <map>
#include <string> 
#include <filesystem> 

namespace fs = std::filesystem; 

class Shop
{
private:
    std::map<std::string, std::tuple<std::string,int,int>> availableItems;
    Items *itemMap;
    std::map<std::string, int> shopConfig;
    std::map<std::string, std::vector<std::pair<std::string, int>>> categoryShop;
public: 
    Shop(const std::string& directory);
    ~Shop();
    void saveShop(const std::string& directory) ;
    std::pair<Item*,int> buyItem(const std::string& itemName, int quantity);
    std::pair<Item*,int> sellItem(const std::string& itemName, int quantity);
    void restock();
    void setStock(const std::string& itemName, int stock);
    int getCurrentStock(const std::string& itemName) const;
    int getPrice(const std::string& itemName) const;
    void displayDetails(std::string itemName) const;
    void displayShop() const;
};


#endif