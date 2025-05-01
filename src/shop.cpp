#include "shop.hpp"
#include "exception.hpp"
#include <iostream>

Shop::Shop(const std::string& directory){
    std:: string filename = directory + "shop.txt";
    this->itemMap = &Items::createFromDirectory(directory);

    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        throw InputOutputException("Directory tidak ditemukan");
    }

    std::ifstream file(filename);
    if (!fs::exists(filename)) {
        throw InputOutputException("File shop.txt tidak ditemukan");
    }
 
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;  

        std::stringstream ss(line);
        std::string name, rarity;
        int basePrice, stock;

        if (ss >> name >> rarity >> basePrice >> stock){ //parsing berhasil
            if(!(stock < 0 && Items::isValidItemRarity(rarity))){
                throw InputOutputException("Stock atau rarity tidak valid"); //eror format file tidak sesuai silahkan masukkan file yang valid
            }

            //validasi nama
            if(!itemMap->lookUpbyName(name)){
                throw InputOutputException("Nama item tidak valid"); //eror format file tidak sesuai silahkan masukkan file yang valid
            }
            
            availableItems[name] = std::make_tuple(rarity, basePrice, stock);
            shopConfig[name] = stock;
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
        if (std::get<2>(item.second) > 0) {
            output << item.first << " " << std::get<0>(item.second) << " " << std::get<1>(item.second) << " " << std::get<2>(item.second) << "\n";
        }
    }

    output.close();
    std::cout << "Shop successfully saved\n";
}

std::pair<int,int> Shop::buyItem(const std::string& itemName, int quantity, Inventory& inventory) {
    auto it = availableItems.find(itemName);

    if (it != availableItems.end()) {
        int price = std::get<1>(it->second);
        int stock = std::get<2>(it->second);
        price *= quantity; 
        switch (std::get<0>(it->second)[0]) {
        case 'S': 
            price*= 50;
            break;
        case 'A': 
            price*= 20;
            break;
        case 'B': 
            price*= 10;
            break;
        case 'C': 
            price*= 5;
            break;
        case 'D': 
            price*= 2;
            break;
        case 'E': 
            price*= 1;
            break;
        default:
            break;
        }
        return std::make_pair(price, stock);
    }else {
        throw ItemNotFound("Item " + itemName + " not found in shop");
    }
}

int Shop::sellItem(const std::string& itemName, int quantity, Inventory& inventory){
    int price;
    
    if (quantity >= 0) {
        try{
            Item *item = itemMap->getItem(itemName);
            inventory.reduceItem(item, quantity);
            std::cout << "Item " << itemName << " sold successfully\n"; 
            price = 0.7*quantity;
            switch (item->getRarity()[0]) {
                case 'S': 
                    price*= 50;
                    break;
                case 'A': 
                    price*= 20;
                    break;
                case 'B': 
                    price*= 10;
                    break;
                case 'C': 
                    price*= 5;
                    break;
                case 'D': 
                    price*= 2;
                    break;
                case 'E': 
                    price*= 1;
                    break;
                default:
                    break;
                }
        } catch (const InputOutputException& e) {
            std::cout << "Error: " << e.what() << "\n";
            return;
        }     
    }else{
        throw ItemNotFound("Item " + itemName + " not found in backpack");
    }
}

void Shop::restock() {
    for (auto& item : availableItems) {
        auto shopItem = shopConfig.find(item.first);
        if (shopItem != shopConfig.end()) {
            std::get<2>(item.second) = shopItem->second; 
        }
    }
}

void Shop::setStock(const std::string& itemName, int stock) {
    auto it = availableItems.find(itemName);
    if (it != availableItems.end()) {
        std::get<2>(it->second) = stock;
    } else {
        std::cout << "Item " << itemName << " not found in shop.\n";
    }
}

int Shop::getCurrentStock(const std::string& itemName) {
    auto it = availableItems.find(itemName);
    if (it != availableItems.end()) {
        return std::get<2>(it->second);
    } else {
        std::cout << "Item " << itemName << " not found in shop.\n";
    }
}

void Shop::displayDetails(std::string itemName) const {
    auto it = availableItems.find(itemName);
    if (it != availableItems.end()) {
        std::cout << "Item: " << itemName << "\n";
        std::cout << "Price: " << std::get<1>(it->second) << "\n";
        std::cout << "Stock: " << std::get<2>(it->second)<< "\n";
        std::cout << "Effects:\n";
        Item * item = itemMap->getItem(itemName);
        for (const auto& effect : item->getEffects()) {
            std::cout << "- " << effect->getName() << "\n";
        }
    } else {
        std::cout << "Item " << itemName << " not found in shop.\n";
    }
}

void Shop::displayShop() const {
    std::cout << "Available items in shop:\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Weapon\n";
    std::cout << "----------------------------------------\n";
    for (const auto& item : availableItems) {
        if(std::get<0>(item.second) == "Weapon") {
            std::cout << item.first << "\n";
        }
        
        // Display items in a 5x2 matrix (5 columns, 2 rows per category)
        for (size_t row = 0; row < 2 && row * 5 < itemCount; ++row) {
            // Print divider line
            std::cout << "+";
            for (size_t col = 0; col < 5 && (row * 5 + col) < itemCount; ++col) {
                std::cout << "--------------------+";
            }
            std::cout << "\n|";
            
            // Print item names
            for (size_t col = 0; col < 5 && (row * 5 + col) < itemCount; ++col) {
                size_t index = row * 5 + col;
                std::string name = items[index].getName();
                std::cout << std::setw(19) << std::left << name << " |";
            }
            std::cout << "\n|";
            
            // Print price and stock
            for (size_t col = 0; col < 5 && (row * 5 + col) < itemCount; ++col) {
                size_t index = row * 5 + col;
                std::string name = items[index].getName();
                int price = availableItems.at(name).first;
                int stock = availableItems.at(name).second;
                
                std::string info = "P:" + std::to_string(price) + " S:" + std::to_string(stock);
                std::cout << std::setw(19) << std::left << info << " |";
            }
            std::cout << "\n+";
            
            // Print bottom divider
            for (size_t col = 0; col < 5 && (row * 5 + col) < itemCount; ++col) {
                std::cout << "--------------------+";
            }
            std::cout << "\n";
        }
    }
}
