#include "../include/Reward.hpp"

#include <iostream>

Reward::Reward() : exp(0), gold(0) {}

Reward::~Reward() {}

int Reward::getExp() const {
    return exp;
}

int Reward::getGold() const {
    return gold;
}

std::map<Item *, int> Reward::getItems() const {
    return items;
}

void Reward::addGold(int gold) {
    if (gold > 0) {
        this->gold += gold;
    }
}

void Reward::addExp(int exp) {
    if (exp > 0) {
        this->exp += exp;
    }
}

void Reward::addItem(Item *item, int count) {
    items[item] += count;
}

// TODO: Catch inventory full when addItem()
void Reward::giveTo(Character* c, Inventory *inv) {
    addExpToCharacter(c, exp);
    addGoldToCharacter(c, gold);
    try {
        for (auto it = items.cbegin(); it != items.cend(); ++it) {
            std::pair<Item*, int> eachItem (it->first, it->second);
            inv->addItem(eachItem);
        }
    } catch (InventoryFull& e) {
        std::cout << e.what() << std::endl;
    }
}

void Reward::giveTo(Inventory *inv) {
    try {
        for (auto it = items.cbegin(); it != items.cend(); ++it) {
            std::pair<Item*, int> eachItem (it->first, it->second);
            inv->addItem(eachItem);
        } 
    } catch (InventoryFull& e) {
        std::cout << e.what() << std::endl;
    }
}

void Reward::displayInfo() {
    // std::cout << "Potential Reward" << std::endl;
    std::cout << "Exp: " << exp << std::endl;
    std::cout << "Gold: " << gold << std::endl;
    std::cout << "Items: " << std::endl;
    
    if (items.empty()) {
        std::cout << "    No items" << std::endl;
        return;
    }

    int ctr = 1;
    for (auto it = items.cbegin(); it != items.cend(); ++it) {
        std::cout << "    " << ctr << ". [" << it->second << "] " << it->first->getName() << std::endl;
    }
}

//TODO: implementasi exp bar
void Reward::addExpToCharacter(Character* c, int exp) {
    if (exp < 0) {
        std::cout << "Reward EXP bernilai negatif (diabaikan)" << std::endl;
        return;
    }

    // Rumus Level Up = Level ^ 1.5 * 100 ^ (1 + 0.005 * Level)
    int expToLevelUp = int(pow(c->getLevel(), 1.5)) * int(pow(100, 1 + 0.005 * c->getLevel()));
    
    c->setExp(c->getExp() + exp);
    if (c->getExp() >= expToLevelUp) {
        // Rumus Bonus Gold Level Up = 100 ^ (1 + 0.01 * Level)
        int bonusGoldLevelUp = int(pow(100, 1 + 0.01 * c->getLevel()));

        int expRemaining = c->getExp() - (expToLevelUp);
        c->levelUp();
        c->setLevel(c->getLevel() + 1);
        c->setExp(expRemaining);
        addGoldToCharacter(c, bonusGoldLevelUp);
        c->setMasteryCost(c->getMasteryCost() + 5);
        std::cout << c->getName() << " naik level ke " << c->getLevel()  << "!\n";
        std::cout << "Bonus Gold Level Up: " << bonusGoldLevelUp << std::endl;
        std::cout << "Bonus Mastery Cost Level Up: +5\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME_REWARD));
        std::cout << "\e[1;1H\e[2J"; //Clear console

        if (expRemaining >= c->getLevel() * 100) {
            addExpToCharacter(c, 0);
        }
    }
}

// Helper menambahkan gold ke character
void Reward::addGoldToCharacter(Character* c, int gold) {
    if (gold < 0) {
        std::cout << "Reward Gold bernilai negatif (diabaikan)" << std::endl;
        return;
    }
    c->setGold(c->getGold() + gold);
}
