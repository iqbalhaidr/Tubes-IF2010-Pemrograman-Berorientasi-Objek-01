#ifndef SHOP_HPP
#define SHOP_HPP

#include "items.hpp"
#include <sstream>
#include <fstream>
#include <map>
#include <string> 
#include <filesystem> 

namespace fs = std::filesystem; 

class Shop
{
private:
    std::map<std::string, std::pair<int,int>> availableItems;
    std::map<std::string, std::vector<Item>> groupedItems;
public:
    Shop(const std::string& directory, const Items& itemMap){
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
    ~Shop();
};


#endif