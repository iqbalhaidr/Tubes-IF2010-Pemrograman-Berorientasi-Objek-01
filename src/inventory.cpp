#include "../include/inventory.hpp"
#include "../include/exception.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>


namespace fs = std::filesystem;

Inventory::Inventory(const std::string& directory, const Items& itemMap)
    : backpack(8, 4) {
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
            if (backpack.get(row, col) == std::pair<std::string, int>()) {
                backpack.set(row, col, {itemId, total});
            } else {
                throw InputOutputException("Slot backpack bertumpuk");
            }
        }
    }

    std::string line2;
    while (std::getline(fileEquipment, line2)) {
        std::string type, itemId;
        std::stringstream ss(line2);

        if (ss >> type >> itemId) {
            if (!(Items::isValidItemType(type) && itemMap.lookup(itemId))) {
                throw InputOutputException("Data equipment tidak valid");
            }
            equipped[type] = itemId;
        }
    }
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
            std::pair<std::string, int> current = backpack.get(i, j);
            if (!(current == std::pair<std::string, int>())) {
                outputBackpack << i << " " << j << " " << current.first << " " << current.second << "\n";
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

void Inventory::addItem(std::pair<const std::string, int>& value) {
    int excessAmount = 0;
    bool foundEmptyCell = false;
    std::pair<int, int> emptyIndex;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::pair<std::string, int> current = backpack.get(i, j);

            if (current.first == value.first && current.second < MAX_ITEM) {
                int total = current.second + value.second;

                if (total <= MAX_ITEM) {
                    backpack.set(i, j, {value.first, total});
                    return;
                } else {
                    backpack.set(i, j, {value.first, MAX_ITEM});
                    excessAmount = total - MAX_ITEM;
                    value.second = excessAmount;
                }
            }

            if (!foundEmptyCell && current == std::pair<std::string, int>()) {
                foundEmptyCell = true;
                emptyIndex = {i, j};
            }
        }
    }

    if (foundEmptyCell && excessAmount > 0) {
        backpack.set(emptyIndex.first, emptyIndex.second, {value.first, excessAmount});
    } else if (excessAmount > 0) {
        throw InputOutputException("Backpack penuh, tidak bisa menambahkan sisa item");
    }
}

void Inventory::reduceItem(const std::string& itemName, int amount) {
    for (int i = 7; i >= 0; --i) {
        for (int j = 3; j >= 0; --j) {
            std::pair<std::string, int> current = backpack.get(i, j);
            if (current.first == itemName && current.second > 0) {
                int toRemove = std::min(current.second, amount);
                current.second -= toRemove;
                amount -= toRemove;
                backpack.set(i, j, current);

                if (amount == 0) return;
            }
        }
    }

    if (amount > 0) {
        throw InputOutputException("Jumlah item tidak cukup untuk dikurangi");
    }
}

void Inventory::setEquippedItem(const std::string& slot, const std::string& item) {
    equipped[slot] = item;
}

Item* Inventory::getEquippedItem(const std::string& slot) const {
    auto it = equipped.find(slot);
    if (it != equipped.end()) {
        return it->second;
    }
    return "";
}

Matrix<std::pair<std::string, int>> Inventory::getBackpack() {
    return backpack;
}
