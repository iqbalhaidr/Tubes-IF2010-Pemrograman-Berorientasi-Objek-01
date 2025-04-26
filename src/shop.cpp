#include "shop.hpp"
#include "exception.hpp"
#include <iostream>

Shop::Shop(const std::string& directory, Items& itemMap){
    std:: string filename = directory + "shop.txt";
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        throw ; //eror folder tidak ada
    }

    std::ifstream file(filename);
    if(file.fail()){
        throw ;//eror file tidak ditemukan
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;  
        std::stringstream ss(line);
        std::string name;
        std::string rarity;
        int basePrice;
        int stock;
        std ::string category;

        if (ss >> name >> rarity >> basePrice >> stock){ //parsing berhasil
            if(!(itemMap.lookUpbyName(name) && Items::isValidItemRarity(rarity))){
                throw ; //eror format file tidak sesuai silahkan masukkan file yang valid
            }
            availableItems[name] = std::make_pair(basePrice, stock);
            shopConfig[name] = std::make_pair(basePrice, stock);
            Item* input = itemMap.getItembyName(name);
            groupedItems[input->getItemType()].push_back(*input);
        }
    }
}

void Shop::saveShop(const std::string& directory, Items& itemMap) {
    std::string filePath = directory + "shop.txt";
    std::ofstream output(filePath);

    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        throw InputOutputException("Directory tidak ditemukan");
    }

    for (const auto& item : availableItems) {
        if (item.second.second > 0) {
            output << item.first << " " << itemMap.getItembyName(item.first)->getRarity() << " " << item.second.first << " " << item.second.second << "\n";
        }
    }

    output.close();
    std::cout << "Shop successfully saved\n";
}



void Shop::buyItem(const std::string& itemName, int quantity, Inventory& inventory) {
    auto it = availableItems.find(itemName);
    if (it != availableItems.end()) {
        int price = it->second.first;
        int stock = it->second.second;

        if (stock >= quantity) {
            // Update stock and add item to inventory
            stock -= quantity;
            inventory.addItem({itemName, quantity});
            setStock(itemName, stock);
            std::cout << "Item " << itemName << " purchased successfully.\n";
        } else {
            std::cout << "Not enough stock for item " << itemName << ".\n";
        }
    } else {
        std::cout << "Item " << itemName << " not found in shop.\n";
    }
}

void Shop::sellItem(const std::string& itemName, int quantity, Inventory& inventory){
    Matrix backpack = inventory.getBackpack();
    int stock = 0;
    for (int i =0; i< backpack.getRows(); i++){
        for(int j = 0; j<backpack.getCols(); j++){
            if (backpack.get(i,j).first == itemName){
                stock = backpack.get(i,j).second;
            }
        }
    }
    if (stock != 0) {
        if(stock >= quantity) {
            inventory.reduceItem(itemName,quantity);
            std::cout << "Item " << itemName << " sold successfully.\n";
        }else {
            std::cout << "Not enough item " << itemName << " in backpack.\n";
        }
    }else{
        std::cout << "Item " << itemName << " not found in backpack.\n";
    }
}

void Shop::restock() {
    for (auto& item : availableItems) {
        auto shopItem = shopConfig.find(item.first);
        if (shopItem != shopConfig.end()) {
            item.second.second = shopItem->second.second; 
        }
    }
}

void Shop::setStock(const std::string& itemName, int stock) {
    auto it = availableItems.find(itemName);
    if (it != availableItems.end()) {
        it->second.second = stock;
    } else {
        std::cout << "Item " << itemName << " not found in shop.\n";
    }
}

void Shop::displayDetails(std::string itemName) const {
    auto it = availableItems.find(itemName);
    if (it != availableItems.end()) {
        std::cout << "Item: " << itemName << "\n";
        std::cout << "Price: " << it->second.first << "\n";
        std::cout << "Stock: " << it->second.second << "\n";
    } else {
        std::cout << "Item " << itemName << " not found in shop.\n";
    }
}

void Shop::displayShop() {
    std::cout << "Available items in shop:\n";
    for ( auto& category: groupedItems) {
        std::cout << "Item: " << category.first << "\n";
        for (auto& item : category.second) {
            std::cout << "  - " << item.getName() << " (Price: " << availableItems.at(item.getName()).first << ", Stock: " << availableItems.at(item.getName()).second << ")\n";
        }
    }
}
