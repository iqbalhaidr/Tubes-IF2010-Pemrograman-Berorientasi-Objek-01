#include "../include/shop.hpp"
#include "../include/exception.hpp"
#include <iostream>

Shop::Shop(const std::string& directory){
    std:: string filename = directory + "shop.txt";
    this->itemMap = new Items(Items::createFromDirectory(directory));
    for (const auto& item : itemMap->getItemMap()) {
        std::string name = item.second->getName();
    }
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
            if(stock < 0 || !Items::isValidItemRarity(rarity)){
                throw InputOutputException("Stock atau rarity tidak valid"); //eror format file tidak sesuai silahkan masukkan file yang valid
            }

            //validasi nama
            if(!itemMap->lookUpbyName(name)){
                throw InputOutputException("Item " + name + " tidak ditemukan di itemMap"); //eror format file tidak sesuai silahkan masukkan file yang valid
            }
            
            availableItems[name] = std::make_tuple(rarity, basePrice, stock);
            shopConfig[name] = stock;
        }
    }

    for (const auto& item : availableItems) {
        Item * itemObj = itemMap->getItembyName(item.first);
        std::string category = itemObj->getItemType();
        categoryShop[category].push_back(std::make_pair(item.first, std::get<2>(item.second)));
    }
    std::cout<<"SELESAI\n";
}

Shop::~Shop() {
    delete itemMap;
}

void Shop::saveShop(const std::string& directory) {
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

std::pair<Item*, int> Shop::buyItem(const std::string& itemName, int quantity) {
    auto it = availableItems.find(itemName);

    if (it != availableItems.end()) {
        int price = std::get<1>(it->second);
        int stock = std::get<2>(it->second);
        if(quantity > stock){
            throw StockError();
        }
        Item *item = itemMap->getItembyName(itemName);
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
        return std::make_pair(item,price);
    }else {
        throw ItemNotFound("Item " + itemName + " not found in shop");
    }
}

std::pair<Item*,int> Shop::sellItem(const std::string& itemName, int quantity){
    int price;
    
    if (quantity >= 0) {
        try{
            Item *item = itemMap->getItembyName(itemName);
            
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
                return {item, price};
        } catch (const InputOutputException& e) {
            std::cout << "Error: " << e.what() << "\n";
            throw; // Rethrow the caught exception
        }     
    }else{
        throw ItemNotFound("Item " + itemName + " not found in backpack");
    }
}

void Shop::restock() {
    for (auto& item : availableItems) {
        std::string name = item.first;
        int stock = shopConfig[name];
        setStock(name, stock);
    }
}

void Shop::setStock(const std::string& itemName, int stock) {
    auto it = availableItems.find(itemName);
    if (it != availableItems.end()) {
        std::get<2>(it->second) = stock;
        Item * item = itemMap->getItembyName(itemName);
        auto category = item->getItemType();
        for(auto& value : categoryShop[category]){
            if(value.first == itemName){
                value.second = stock;
                break;
            }
        }
    } else {
        std::cout << "Item " << itemName << " not found in shop.\n";
    }
}

int Shop::getCurrentStock(const std::string& itemName) const {
    auto it = availableItems.find(itemName);
    if (it != availableItems.end()) {
        return std::get<2>(it->second);
    } else {
        throw StockError("Item " + itemName + " not found in shop");
    }
}

int Shop::getPrice(const std::string& itemName) const {
    auto it = availableItems.find(itemName);
    if (it != availableItems.end()) {
        return std::get<1>(it->second);
    } else {
        throw ItemNotFound("Item " + itemName + " not found in shop");
    }
}

void Shop::displayDetails(std::string itemName) const {
    auto it = availableItems.find(itemName);
    if (it != availableItems.end()) {
        std::cout << "Item: " << itemName << "\n";
        std::cout << "Price: " << std::get<1>(it->second) << "\n";
        std::cout << "Stock: " << std::get<2>(it->second)<< "\n";
        std::cout << "Effects:\n";
        Item * item = itemMap->getItembyName(itemName);
        for (const auto& effect : item->getEffects()) {
            std::cout << "- " << effect->getName() << "\n";
        }
    } else {
        std::cout << "Item " << itemName << " not found in shop.\n";
    }
}

void Shop::displayShop() const {
    std::cout << "========== Shop Items ==========\n";
    for (const auto& category : categoryShop) {
        std::cout << "Category: " << category.first << "\n";
        std::cout << std::left 
                  << std::setw(20) << "Item Name" 
                  << std::setw(10) << "Price" 
                  << std::setw(10) << "Stock" << "\n";
        std::cout << std::string(40, '-') << "\n";

        for (const auto& item : category.second) {
            std::cout << std::left 
                      << std::setw(20) << item.first 
                      << std::setw(10) << getPrice(item.first) 
                      << std::setw(10) << item.second << "\n";
        }

        std::cout << "\n";
    }
}

