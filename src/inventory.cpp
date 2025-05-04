#include "../include/inventory.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../include/character.hpp"
#include "../include/exception.hpp"
#include "../include/matrix.hpp"

namespace fs = std::filesystem;

std::string Inventory ::centerText(const std::string& text, int width) {
    int padding = width - text.length();
    if (padding <= 0) return text;  // Jika teks lebih panjang, return as-is

    int left = padding / 2;
    int right = padding - left;

    return std::string(left, ' ') + text + std::string(right, ' ');
}

Inventory Inventory ::loadInventory(const std::string& directory,
                                    const Items& itemMap) {
    Matrix<std::pair<Item*, int>> backp(8, 4);
    std::map<std::string, Item*> equippedItem;

    std::string filePathBackpack = directory + "backpack.txt";
    std::string filePathEquipment = directory + "equipment.txt";

    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        throw InputOutputException("Directory tidak valid");
    }

    std::ifstream fileBackpack(filePathBackpack);
    std::ifstream fileEquipment(filePathEquipment);

    if (fileBackpack.fail()) {
        throw InputOutputException("File backpack.txt gagal dibuka");
    }
    if (fileEquipment.fail()) {
        throw InputOutputException("File equipment.txt gagal dibuka");
    }

    std::string line1;
    while (std::getline(fileBackpack, line1)) {
        int row, col, total;
        std::string itemId;
        std::stringstream ss(line1);

        if (ss >> row >> col >> itemId >> total) {
            if (backp.isEmptyCell(row, col)) {  // jika kosong

                Item* cloned = itemMap.getItem(itemId);
                // cout<<"INI NAMA DAN TYPENYA : " << cloned->getName() << " dan " << cloned->getItemType();
                if((cloned->getItemType() == "Weapon" || cloned->getItemType() == "Armor") && total >1){
                    cout<<cloned->getId()<<"\n";
                    cout<<cloned->getName()<<"\n";
                    cout<<total<<"\n";
                    throw InputOutputException(
                        "Jumlah Weapon atau Armor dalam backpack tidak boleh lebih dari 1");
                }
                backp.set(row, col, {cloned, total});  // add
                // std::cout << cloned->getId() << " INI NAMANYA\n";
            } else {
                throw InputOutputException(
                    "Slot backpack bertumpuk");  // untuk config ga boleh
                                                 // bertumpuk
            }
        }
    }

    std::string line2;  // bagian equipment
    while (std::getline(fileEquipment, line2)) {
        std::string type, itemId;
        std::stringstream ss(line2);

        if (ss >> type) {
            if (ss >> itemId) {
                if (!(Items::isValidItemType(type) && itemMap.lookup(itemId))) {
                    throw InputOutputException("Data equipment tidak valid");
                }
                equippedItem[type] = itemMap.getItem(itemId);
            } else {
                equippedItem[type] = nullptr;
            }
        }
    }
    return Inventory(backp, equippedItem);
}

Inventory::Inventory(const Matrix<std::pair<Item*, int>>& backp,
                     const std::map<std::string, Item*>& equippedItem) {
    this->backpack = backp;
    this->equipped = equippedItem;
}

void Inventory::saveInventory(const std::string& directory) {
    std::string filePathBackpack = directory + "backpack.txt";
    std::string filePathEquipment = directory + "equipment.txt";

    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        throw InputOutputException("Directory tidak ditemukan");
    }

    std::ofstream outputBackpack(filePathBackpack);
    std::ofstream outputEquipment(filePathEquipment);

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (!(backpack.isEmptyCell(i, j))) {
                auto current = backpack.get(i, j);
                outputBackpack << i << " " << j << " " << current.first->getId()
                               << " " << current.second << "\n";
            }
        }
    }

    for (const auto& equipment : equipped) {
        outputEquipment << equipment.first << " " ;
        if(equipment.second == nullptr){
            outputEquipment << " " << "\n";
        }
        else{
            outputEquipment << equipment.second->getId() << "\n";
        }
    }

    outputBackpack.close();
    outputEquipment.close();
    std::cout << "Inventory successfully saved\n";
}

void Inventory::addItem(std::pair<Item*, int>& value) {
    Item* item = value.first;
    int& quantity = value.second;
    bool isStackable = item->isStackable();
    
    cout<< isStackable<<" INI STATE STACKABLE ATAU NGGA\n";
    if (isStackable) {
        auto existingItem = getIdxItembyId(item->getId());
        if (existingItem.first != -1) {
            cout<<existingItem.first<<","<< existingItem.second<<" INI EXIST DIMANA\n" ;
            for (int i = 0; i < 8 && quantity > 0; ++i) {
                for (int j = 0; j < 4 && quantity > 0; ++j) {
                    std::pair<Item*, int> current = backpack.get(i, j);
                    
                    if (current.first!=nullptr &&*current.first == *item && current.second < MAX_ITEM) {
                        int spaceAvailable = MAX_ITEM - current.second;
                        int amountToAdd = std::min(spaceAvailable, quantity);
                        // cout<<current.first->getName() << " KIRI NAME CURRENT KANAN NAME ITEM"<< item->getName()<<"\n";
                        cout<<i<<","<<j<<" INI DIA I J NYA SAAT EXIST\n";
                        backpack.set(i, j, {current.first, current.second + amountToAdd});
                        quantity -= amountToAdd;
                    }
                }
            }
        }
    }

    // tambahkan sisa
    for (int i = 0; i < 8 && quantity > 0; ++i) {
        for (int j = 0; j < 4 && quantity > 0; ++j) {
            if (backpack.isEmptyCell(i, j)) {
                if (isStackable && quantity > 0) {
                    int amountToAdd = std::min(MAX_ITEM, quantity);
                    backpack.set(i, j, {item, amountToAdd});
                    quantity -= amountToAdd;
                } else if (quantity > 0) {
                    backpack.set(i, j, {item, 1});
                    quantity -= 1;
                }
            }
        }
    }

    // Jika masih ada sisa yang tidak bisa dimasukkan, lempar exception
    if (quantity > 0) {
        throw InventoryFull("Backpack penuh, tidak bisa menambahkan sisa item", quantity);
    }
}

void Inventory::reduceItem(const Item* item, int target) {
    bool isStackAble = item->isStackable();
    for (int i = 7; i >= 0; --i) {
        for (int j = 3; j >= 0; --j) {
            std::pair<Item*, int> current = backpack.get(i, j);
            if (current.first!=nullptr && *current.first == *item && current.second > 0 && isStackAble) {
                int toRemove = std::min(current.second, target);
                current.second -= toRemove;
                target -= toRemove;
                if(current.second == 0){
                    cout<<i<<","<<j<<" INI DIA I J NYA SAAT SET\n";
                    backpack.set(i, j, std::pair<Item*, int>());
                }
                else{
                    backpack.set(i, j, current);
                }

                if (target == 0) return;
            }
            else if(current.first!=nullptr && *current.first == *item && current.second > 0){
                target-=1;
                current.second-=1;
                if(current.second == 0){
                    backpack.set(i, j, std::pair<Item*, int>());
                }
                else{
                    backpack.set(i, j, current);
                }

                if (target == 0) return;
            }
        }
    }

    if (target > 0) {
        throw InputOutputException(
            "Jumlah item tidak cukup untuk dikurangi");  // dont forget to
                                                         // handle try and catch
    }
}

void Inventory::equipItem(std::string slot, Character& orang, Item* item, Unit& target){
    for (Effect* effect : item->getEffects()) {
        orang.addActiveEffect(effect);
    }

    setEquipped(slot, item);
    reduceItem(item, 1);
}

void Inventory::unequipItem(Character& orang, const std::string& slot, Unit& target){
    Item* item = equipped[slot];
    if (item == nullptr){
        return;
    } 

    equipped[slot] = nullptr;
    std:: pair<Item*,int> p = {item,1};
    addItem(p);
    

    for (Effect* effect : item->getEffects()) {
        orang.removeActiveEffect(effect);
    }
}


void Inventory::handleNonConsumable(Item* item, Character& orang, Unit& target) {
    std::string type = item->getItemType();

    if (type == "Weapon") {
        unequipItem(orang, "WEAPON", target);
        equipItem("WEAPON", orang, item, target);
    }
    else if (type == "Pendant") {
        unequipItem(orang, "PENDANT", target);
        equipItem("PENDANT", orang, item, target);
    }
    else if (type == "Armor") {
        std::vector<std::string> armorSlots = {"ARMOR_BODY", "ARMOR_FOOT", "ARMOR_HEAD"};
        
        // Cari slot kosong terlebih dahulu
        for (const auto& slot : armorSlots) {
            if (this->getEquippedItem(slot) == nullptr) {
                equipItem(slot, orang, item, target);
                return;
            }
        }

        // Jika tidak ada slot kosong, cari armor dengan stat terendah
        std::string minSlot = "";
        int minStat = INT_MAX;
        for (const auto& slot : armorSlots) {
            Item* equipped = this->getEquippedItem(slot);
            if (equipped && equipped->getFinalStat() < minStat) {
                minStat = equipped->getFinalStat();
                minSlot = slot;
            }
        }

        if (!minSlot.empty()) {
            unequipItem(orang, minSlot, target);
            equipItem(minSlot, orang, item, target);
        }
    }
}

void Inventory::handleConsumable(Item* item, Character& orang, Unit& target) {
    for (Effect* effect : item->getEffects()) {
        if (effect->isThrowable()) {
            target.addActiveEffect(effect);
        } else {
            orang.addActiveEffect(effect);
        }
    }
}

void Inventory::useItem(const std::string itemID, Character& orang, const Items& itemMap, Unit& target) {
    auto [item, count] = this->getItemById(itemID);
    if (item == nullptr) return;

    if (!item->isConsumable()) {
        handleNonConsumable(item, orang, target);
    } else {
        handleConsumable(item, orang, target);
    }
}

std:: pair<int,int>  Inventory::getIdxItembyId(const std::string& itemID) const{
    auto lambda = [itemID] (const std::pair<Item*, int>& a){
        if(a.first != nullptr && itemID == a.first->getId()){
            cout <<"Ini tu stackable atau ngga "<<a.first->isStackable() <<"\n";
            cout<<itemID << "INI ITEM ID DAN KANANNYA ITEM DALAM BACKPACK NAMA: "<<a.first->getName() <<"\n";
        }
         return a.first != nullptr && itemID == a.first->getId();
    };
    auto idxItemInBackpack = backpack.isInMatrix(lambda);
    return idxItemInBackpack;
}

std::string Inventory::getEquippedItemId(const std::string& slot) const {
    auto it = equipped.find(slot);
    if (it != equipped.end()) {
        return it->second->getId();
    }
    return "";
}



void Inventory :: displayBackpack(){
    auto txtGenerator = [](std::pair<Item*, int> p){return p.first->getId() +" ("+ std::to_string(p.second) +") " + p.first->getItemType() ;};
    std::string item = "";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            if (backpack.isEmptyCell(i, j)) {
                item = "";
            } 
            else {
                item = txtGenerator(backpack.get(i, j));
            }
            std::cout<<"|"<<Inventory::centerText(item, 20)<<"|";
        }   
        cout<<"\n";
    }
}

std::pair<Item *, int>  Inventory :: getItemById(const std::string& itemId){
    auto idx = getIdxItembyId(itemId);
    if(idx.first ==-1 && idx.second==-1) return {nullptr, -1};
    return backpack.get(idx.first, idx.second);
}

void Inventory::setEquipped(const std::string& slot, Item* item){
    equipped[slot] = item;
}

void Inventory::displayEquipment(){
    for (const auto& [key, value] : equipped) {
        if(!(value == nullptr)){
            std::cout << key << " => " << value->getName() << std::endl;
        }
        else{
            std::cout << key << " => " << "KOSONG" << std::endl;
        }
       
    }
}

std::pair<Item *, int> Inventory::getItemBackpackByName(const std::string& itemName){
    cout<< backpack.get(0,5).second << " WOI INI BERAPA COUNTNYA\n";
    auto lambda = [itemName] (const std::pair<Item*, int>& a){
        return a.first != nullptr && itemName == a.first->getName();
    };
    auto idxItem = backpack.isInMatrix(lambda);
    if(idxItem.first ==-1 && idxItem.second==-1) return {nullptr, -1};
    return backpack.get(idxItem.first, idxItem.second);
}

int Inventory::getItemQtyInInvent(const std::string& itemName){
    int qty = 0;
    cout<< backpack.get(0,5).second << "WOI INI BERAPA COUNTNYA\n";
    for(int i=0; i<8; i++){
        for(int j = 0; j<4; j++){
            auto curr = backpack.get(i,j);
            if(curr.first!= nullptr && curr.first->getName() == itemName){
                qty+=curr.second;
            }
        }
    }

    return qty;
}

void Inventory:: displayBackpackDetails() {
    std::vector<std::string> txt;
    std::cout<<std::endl;

    for(int i=0; i< 8; i++){
        for(int j = 0; j<4; j++){
            auto back = backpack.get(i, j);
            Item* item = back.first;
            if (item != nullptr) {
                std::string generator = item->getId() + ": " + item->getName();
                if (std::find(txt.begin(), txt.end(), generator) == txt.end()) {
                    txt.push_back(generator);
                }
            }
        }
    }
    for (const auto& line : txt) {
        std::cout << line << std::endl;
    }
    std::cout<<std::endl;
}