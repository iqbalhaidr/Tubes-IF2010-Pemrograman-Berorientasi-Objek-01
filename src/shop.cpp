#include "shop.hpp"
#include "exception.hpp"
#include <iostream>

Shop::Shop(const std::string& directory, const Items& itemMap){
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

        if (ss >> name >> rarity >> basePrice >> stock){ //parsing berhasil
            if(!(itemMap.lookUpbyName(name) && Items::isValidItemRarity(rarity))){
                throw ; //eror format file tidak sesuai silahkan masukkan file yang valid
            }
        }
    }

}

Shop::~Shop(){}

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

