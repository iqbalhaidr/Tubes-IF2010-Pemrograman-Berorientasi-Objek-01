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

void Reward::giveTo(Character* c, Inventory *inv) {
    addExpToCharacter(c, exp);
    addGoldToCharacter(c, gold);
    for (auto it = items.cbegin(); it != items.cend(); ++it) {
        std::pair<Item*, int> eachItem (it->first, it->second);
        inv->addItem(eachItem);
    }
}

void Reward::giveTo(Inventory *inv) {
    for (auto it = items.cbegin(); it != items.cend(); ++it) {
        std::pair<Item*, int> eachItem (it->first, it->second);
        inv->addItem(eachItem);
    } 
}

void Reward::displayInfo() {
    std::cout << "Current Reward" << std::endl;
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

void Reward::addExpToCharacter(Character* c, int exp) {
    if (exp < 0) {
        std::cout << "Exp reward cannot be negative" << std::endl;
        return;
    }
    c->setExp(c->getExp() + exp);
    if (c->getExp() >= c->getLevel() * 100) { // INI MASIH MANUAL
        c->levelUp();
    }
}

// Helper menambahkan gold ke character
void Reward::addGoldToCharacter(Character* c, int gold) {
    if (gold < 0) {
        std::cout << "Gold reward cannot be negative" << std::endl;
        return;
    }
    c->setGold(c->getGold() + gold);
}
