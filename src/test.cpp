#include <iostream>
#include <vector>
#include <map>
#include <limits>

#include "../include/Randomizer.hpp"
#include "../include/items.hpp"
#include "../include/inventory.hpp"
#include "../include/Dungeon.hpp"
#include "../include/fighter.hpp"

using namespace std;

void switchTest(int i) {
    switch (i) {
        case 1:
            cout << "ini masuk 1" << endl;
            break;
        case 2:
            cout << "ini masuk 2" << endl;
            break;
        case 3:
            cout << "ini masuk 3" << endl;
            break;
        default:
            cout << "ini selain 1 2 3" << endl;
            break;
    }
}

// void chanceTest() {
//     int ctr = 0;
//     int n = 10000;
//     for (int i = 0; i < n; i++) {
//         if (Randomizer::chance(0.01f)) {
//             ctr++;
//         }
//     }
//     cout << "ini chance true " << ((float) ctr/ (float) n) * 100.00f << "%" << endl;
// }

/*
void mapTest() {
    std::map<char*, int> m;
    char* a = "a";
    char* b = "b";

    m[a] += 3;
    m[b] += 1;
    m[a] += 2;

    std::map<char*, int>::const_iterator it = m.begin();
    for (auto it = m.cbegin(); it != m.cend(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
}
*/

map<string, int> mapReturnTest() {
    map<string, int> m;
    m["a"] = 1;
    m["b"] = 2;
    m["c"] = 3;
    return m;
}

int inputOption() {
    int opt;
    bool isValid = false;
    while (!isValid) {
        std::cout << "Choose your action: " << std::endl;
        std::cout << "1. Attack" << std::endl;
        std::cout << "2. Use Skill" << std::endl;
        std::cout << "3. Use Item" << std::endl;
        std::cout << "4. Run Away" << std::endl;
        std::cin >> opt;

        if (std::cin.fail()) {
            std::cin.clear(); // reset fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // buang sisa input
            std::cout << "Invalid input. Please enter a number between 1 and 4." << std::endl;
        } else if (opt >= 1 && opt <= 4) {
            isValid = true;
        } else {
            std::cout << "Invalid option. Please try again." << std::endl;
        }
    }

    return opt;
}

// g++ test.cpp Randomizer.cpp items.cpp item.cpp effect.cpp EffectDamage.cpp EffectDefensive.cpp EffectHealthRegen.cpp EffectManaRegen.cpp EffectPoison.cpp
void itemsParserTest() {
    Items items = Items::createFromDirectory("../data/");
    std::map<std::string, Item*> itemMap = items.getItemMap();
    for (auto item : itemMap) {
        std::cout << item.first << " ";
        std::cout << item.second->getId() << " ";
        std::cout << item.second->getName() << " ";
        std::cout << item.second->getItemType() << " ";
        std::cout << item.second->getRarity() << " ";
        std::cout << item.second->getBaseStat() << "\n";
        for (auto effect : item.second->getEffects()) {
            std::cout << "    " << effect->getName() << " ";
            std::cout << effect->getDescription() << " ";
            std::cout << effect->getDuration() << " ";
            std::cout << effect->getRemainingDuration() << "\n";
        }
    }
}

void itemInventoryParserTest(){
    Items items = Items::createFromDirectory("../data/");
    Inventory inv = Inventory::loadInventory("../data/", items);
    inv.displayBackpack();
}


void dungeonTest() {
    Items items = Items::createFromDirectory("../data/");
    Mobloot mobLoot = Mobloot("../data/", items);
    Dungeon ds ("E", mobLoot, items);
    Fighter f ("player1", 100, 100, 100, 100, 100, 100, 100);
    Inventory inv = Inventory::loadInventory("C:/Users/IQBAL-LAPTOP/IF/if2010-2425-tubes-1-lah/data/", items);
    // ds.displayInfo();
    ds.start(f, inv, items);
}

int main() {
    // int i = 5;
    // for (; i < 10; i++) {
    //     cout << i << endl;
    // }
    // for (int i = 0; i < 5; i++) {
    //     switchTest(Randomizer::random(1, 3));
    //     cout << "================\n";
    // }
    // chanceTest();
    // randomTest();
    // mapTest();
    // cout << mapReturnTest()["a"] << endl;
    // cout << inputOption() << endl;
    itemsParserTest();
    itemInventoryParserTest();
    // itemsParserTest();
    // dungeonTest();
}