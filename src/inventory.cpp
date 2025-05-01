#include "../include/inventory.hpp"
#include "../include/matrix.hpp"
#include "../include/exception.hpp"
#include "../include/character.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>


namespace fs = std::filesystem;

std::string Inventory :: centerText(const std::string &text, int width) {
    int padding = width - text.length();
    if (padding <= 0) return text;  // Jika teks lebih panjang, return as-is
    
    int left = padding / 2;
    int right = padding - left;
    
    return std::string(left, ' ') + text + std::string(right, ' ');
}
    

Inventory Inventory :: loadInventory(const std::string& directory, const Items& itemMap){ 
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
            if (backp.isEmptyCell(row,col)) { // jika kosong
                
                Item* cloned =itemMap.getItem(itemId);
                backp.set(row, col, {cloned , total}); //add
                std::cout << cloned->getId() << " INI NAMANYA\n";
            } else {
                throw InputOutputException("Slot backpack bertumpuk"); //untuk config ga boleh bertumpuk
            }
        }
    }

    std::string line2;  //bagian equipment
    while (std::getline(fileEquipment, line2)) {
        std::string type, itemId;
        std::stringstream ss(line2);

        if (ss >> type) {
            if(ss >> itemId){
                if (!(Items::isValidItemType(type) && itemMap.lookup(itemId))) {
                    throw InputOutputException("Data equipment tidak valid");
                }
                equippedItem[type] = itemMap.getItem(itemId);
            }
            else{
                equippedItem[type] = nullptr;
            }

        }
    }
    return Inventory(backp,equippedItem);
}


Inventory::Inventory(const Matrix<std::pair<Item*, int>>& backp, const std::map<std::string, Item*>& equippedItem){
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
            if (!(backpack.isEmptyCell(i,j))) {
                auto current = backpack.get(i,j);
                outputBackpack << i << " " << j << " " << current.first->getId() << " " << current.second << "\n";
            }
        }
    }

    for (const auto& equipment : equipped) {
        outputEquipment << equipment.first << " " << equipment.second << "\n";
    }

    outputBackpack.close();
    outputEquipment.close();
    std::cout << "Inventory successfully saved\n";
}




void Inventory::addItem(std::pair<Item*, int>& value) {
    Item* item = value.first;
    int& quantity = value.second;
    bool isStackable = item->isStackable();
    
    if (isStackable) {
        auto existingItem = getIdxItembyId(item->getId());
        if (existingItem.first != -1) {
            for (int i = 0; i < 8 && quantity > 0; ++i) {
                for (int j = 0; j < 4 && quantity > 0; ++j) {
                    std::pair<Item*, int> current = backpack.get(i, j);
                    
                    if (current.first == item && current.second < MAX_ITEM) {
                        int spaceAvailable = MAX_ITEM - current.second;
                        int amountToAdd = std::min(spaceAvailable, quantity);
                        
                        backpack.set(i, j, {current.first, current.second + amountToAdd});
                        quantity -= amountToAdd;
                    }
                }
            }
        }
    }
    
    //tambahkan sisa
    for (int i = 0; i < 8 && quantity > 0; ++i) {
        for (int j = 0; j < 4 && quantity > 0; ++j) {
            if (backpack.isEmptyCell(i, j)) {
                if (isStackable && quantity>0) {
                    int amountToAdd = std::min(MAX_ITEM, quantity);
                    backpack.set(i, j, {item, amountToAdd});
                    quantity -= amountToAdd;
                } 
                else if(quantity>0){
                    backpack.set(i, j, {item, 1});
                    quantity -= 1;
                }
            }
        }
    }
    
    // Jika masih ada sisa yang tidak bisa dimasukkan, lempar exception
    if (quantity > 0) {
        throw InputOutputException("Backpack penuh, tidak bisa menambahkan sisa item");
    }
}

void Inventory::reduceItem(const Item* item, int target) {
    bool isStackAble = item->isStackable();
    for (int i = 7; i >= 0; --i) {
        for (int j = 3; j >= 0; --j) {
            std::pair<Item*, int> current = backpack.get(i, j);
            if (current.first == item && current.second > 0 && isStackAble) {
                int toRemove = std::min(current.second, target);
                current.second -= toRemove;
                target -= toRemove;
                backpack.set(i, j, current);

                if (target == 0) return;
            }
            else if(current.first == item && current.second > 0){
                target-=1;
                current.second-=1;
                backpack.set(i, j, current);

                if (target == 0) return;
            }
        }
    }

    if (target > 0) {
        throw InputOutputException("Jumlah item tidak cukup untuk dikurangi");  // dont forget to handle try and catch
    }
}

void Inventory::useItem(const std::string itemID, Character& orang, const Items& itemMap) {
    auto idxItem = getIdxItembyId(itemID);
    if (idxItem.first == -1 && idxItem.second == -1){
        return; // bisa throw atau error handling lainnya
    }

    auto itemInInventory = backpack.get(idxItem.first, idxItem.second);
    if (!(itemInInventory.first->isConsumable())) {
        std::string type = itemInInventory.first->getItemType();

        if (type == "Weapon") {
            //unequip Current Weapon
            unequipItem(orang, "WEAPON");
            generalEquip("WEAPON", orang, itemInInventory.first);
            orang.setAttackDamage(orang.getAttackDamage() + itemInInventory.first->getFinalStat());
        }

        else if (type == "Armor") {
            std::vector<std::string> armorSlots = {"ARMOR_BODY", "ARMOR_FOOT", "ARMOR_HEAD"};

            // Find Empty Slot
            for (const std::string& slot : armorSlots) {
                if (equipped[slot] == nullptr) {
                    equipped[slot] = itemInInventory.first;
                    reduceItem(itemInInventory.first, 1);
                    return;
                }
            }

            // No empty slot
            std::string minSlot = "";
            int minStat = INT_MAX;
            for (const auto& slot : armorSlots) {
                if (equipped[slot] != nullptr) {
                    int stat = equipped[slot]->getFinalStat();
                    if (stat < minStat) {
                        minStat = stat;
                        minSlot = slot;
                    }
                }
            }

            if (minSlot != "") {
                generalUnequip(minSlot, orang);
                generalEquip(minSlot, orang, itemInInventory.first);
            }
        }

        else if (type == "Pendant") {
            if(!(equipped["PENDANT"] == nullptr)){
                generalUnequip("PENDANT", orang);
            }  
            generalEquip("PENDANT", orang, itemInInventory.first);
        }
    }
    else{
        reduceItem(itemInInventory.first,1);
        std::vector<Effect*> effectItem = itemInInventory.first->getEffects();
        for (Effect* e : effectItem){
            orang.addActiveEffect(e);
        }
    }
}

void Inventory :: generalEquip(std::string slot, Character& orang, Item* item){
    reduceItem(item,1);
    std::vector<Effect*> effectItem = item->getEffects();
    for (Effect* e : effectItem){
        orang.addActiveEffect(e);
    }
    equipped[slot] = item;
}

void Inventory :: unequipItem(Character& orang, const std::string& slot){
    if(slot == "WEAPON"){
        if(!(equipped["WEAPON"] == nullptr)){
            orang.setAttackDamage(orang.getAttackDamage() - equipped["WEAPON"]->getFinalStat());
            generalUnequip("WEAPON", orang);
        }
    }
    else{
        generalUnequip(slot, orang);
    }

}

void Inventory :: generalUnequip(std::string slot, Character& orang){
    std::pair<Item*, int> item = {equipped[slot],1};
    addItem(item);
    std::vector<Effect*> effectItem = equipped[slot]->getEffects();
    for (Effect* e : effectItem){
        orang.removeActiveEffect(e);
    }
    equipped[slot] = nullptr;
}

std:: pair<int,int>  Inventory::getIdxItembyId(const std::string& itemID) const{
    auto lambda = [itemID] (const std::pair<Item*, int>& a){
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
    auto txtGenerator = [](std::pair<Item*, int> p){return p.first->getId() +" ("+ std::to_string(p.second) +") " ;};
    std::string item = "";
    for(int i=0; i<8; i++){
        for(int j = 0; j<4; j++){
            if(backpack.isEmptyCell(i,j)){
                item="";
            }
            else{

                item=txtGenerator(backpack.get(i,j));
            }
            std::cout<<"|"<<Inventory::centerText(item, 10)<<"|";
        }   
        cout<<"\n";
    }
}
