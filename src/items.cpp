#include "../include/items.hpp"
#include "../include/item.hpp"
#include "../include/Weapon.hpp"
#include "../include/Armor.hpp"
#include "../include/Potion.hpp"
#include "../include/Pendant.hpp"
#include "../include/exception.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

Items Items :: createFromDirectory(const std::string& directory) {
    std::map<std::string, Item*> itemMap;
    std::string filename = directory + "item.txt";
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        throw InputOutputException("Directory tidak ditemukan");
    }

    std::ifstream file(filename);
    if (file.fail()) {
        throw InputOutputException("File item.txt tidak ditemukan");
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        std::string id, name, type, rarity;
        int level;
        double baseStat;
        std::vector<Effect*> effects;
        std::string temp;
        
        if (ss >> id >> name >> type >> rarity >> baseStat) {
            if (!(Items::isValidItemType(type) && Items::isValidItemRarity(rarity))) {
                throw InputOutputException("Tipe atau rarity tidak valid");
            }
            // std::cout<<"INI ADA WOI\n";
            // std::cout<<name;

            Effect* effect;
            while (ss >> temp) {
                if (temp == "-") break;  
                effects.push_back(Effect::createEffect(temp));
            }

            // TODO: VALIDASI EFEK
            Item * newItem;
            if(type == "Weapon"){
                newItem = new Weapon(id, name, type, rarity, baseStat, effects);  
            }
            else if(type == "Armor"){
                newItem = new Armor(id, name, type, rarity, baseStat, effects);  
            }
            else if(type == "Pendant"){
                newItem = new Pendant(id, name, type, rarity, baseStat, effects);  
            }
            else if(type == "Potion"){
                newItem = new Potion(id, name, type, rarity, baseStat, effects);  
            }
            
      
            itemMap.insert(std::make_pair(id, newItem));
        } else {
            throw InventoryEror("Format baris salah di file item.txt");
        }
    }
    Items listItem (itemMap);
    
    return listItem;
}


Items :: Items(std::map<std::string, Item*> itemMap){
    this->itemMap = itemMap;
}

Items::~Items() {
    for (auto& pair : itemMap) {
        delete pair.second;
    }
    itemMap.clear();
}

void Items::addItem(const std::string& id, Item* item) {
    itemMap[id] = item;
}

bool Items::lookup(const std::string& id) const {
    return itemMap.find(id) != itemMap.end();
}

bool Items::lookUpbyName(const std::string& Name) const {
    for (const auto& item : itemMap) {
        if (item.second->getName() == Name) {
            return true;
        }
    }
    return false;
}

Item* Items::getItem(const std::string& id) const {
    auto it = itemMap.find(id);
    if (it != itemMap.end()) return it->second->cloneItem();
    return nullptr;
}

Item* Items::getItembyName(const std::string& Name) {
    for (const auto& item : itemMap) {
        if (item.second->getName() == Name) {
            return item.second;
        }
    }
    return nullptr;
}

void Items::save(const std::string& directory) const {
    std::string filename = directory + "item.txt";

    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        throw InventoryEror("Directory tidak ditemukan");
    }

    std::ofstream outputFile(filename);
    for (const auto& item : itemMap) {
        outputFile << item.first << " "
                   << item.second->getName() << " "
                   << item.second->getItemType() << " "
                   << item.second->getRarity() << " "
                   << item.second->getBaseStat() << " ";
        for (const auto& effect : item.second->getEffects()) {
            outputFile << effect << " ";
        }
        outputFile << "\n";
    }

    outputFile.close();
    std::cout << "Data saved to " << filename << std::endl;
}

bool Items::isValidItemType(const std::string& type) {
    return (type == "Weapon" || type == "Armor" ||
            type == "Potion" || type == "Pendant" ||
        type == "WEAPON" || type== "ARMOR_HEAD" || type== "ARMOR_BODY" || type== "ARMOR_FOOT"
        || type== "PENDANT");
}

bool Items::isValidItemRarity(const std::string& rarity) {
    return (rarity == "A" || rarity == "B" || rarity == "C" ||
            rarity == "D" || rarity == "E" || rarity == "S");
}
