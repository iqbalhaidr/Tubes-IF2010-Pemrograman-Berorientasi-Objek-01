#include "../include/Mobloot.hpp"
#include "../include/exception.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>


namespace fs = std::filesystem;

Mobloot::Mobloot(const string& directory, const Items& itemMap) {
    std::string filepath = directory + "mobloot.txt";

    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        throw InputOutputException("Directory tidak valid");
    }

    std::ifstream file(filepath);

    if (file.fail()) {
        throw InputOutputException("File mobloot.txt gagal dibuka");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string mobName;
        std::string itemID;
        double itemDropRate;

        if (ss >> mobName >> itemID >> itemDropRate) {
            if (!itemMap.lookup(itemID)) {
                throw InputOutputException("Item ID tidak valid: " + itemID);
            }
            if (dropRate < 0.0 || dropRate > 1.0) {
                throw InputOutputException("Drop rate tidak valid: " + itemDropRate);
            }

            this->MobLoots[mobName].emplace_back(itemMap.getItem(itemID), itemDropRate);
        } else {
            throw InputOutputException("Format baris salah di file mobloot.txt");
        }

    }
    file.close();


}

Mobloot::~Mobloot() {
    for (auto& loot : MobLoots) {
        for (auto& item : loot.second) {
            delete item.first; 
        }
    }
    MobLoots.clear();
}

vector<pair<Item*, double>> Mobloot::getLootforMob(const string& name) {
    auto it = MobLoots.find(name);
    if (it != MobLoots.end()) {
        return it->second;
    }
    return vector<pair<Item*, double>>(); 
}






