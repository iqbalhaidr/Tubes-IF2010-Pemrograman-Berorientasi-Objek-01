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
    items[item] = count;
}

void Reward::displayInfo() {
    std::cout << "Current Reward" << std::endl;
    std::cout << "Exp: " << exp << std::endl;
    std::cout << "Gold: " << gold << std::endl;
    std::cout << "Items: " << std::endl;

    std::map<Item *, int>::const_iterator i = items.begin();
    int ctr = 1;
    for (; i != items.end(); i++) {
        std::cout << "    " << ctr << ". " << i->second << " " << i->first->getName() << std::endl;
        ctr++;
    }
}

// void Reward::giveTo(Char* c, Inventory *inv) {
//     c.addExp(exp);
//     c.addGold(exp);
//     std::map<Item *, int>::const_iterator i = items.begin();
//     for (; i != items.end(); i++) {
//         std::pair<const Item*, int> eachItem (i->first, i->second);
//         inv->addItem(eachItem);
//     }
// }

// void Reward::giveTo(Inventory *inv) {
//     std::map<Item *, int>::const_iterator i = items.begin();
//     for (; i != items.end(); i++) {
//         std::pair<const Item*, int> eachItem (i->first, i->second);
//         inv->addItem(eachItem);
//     }
// }