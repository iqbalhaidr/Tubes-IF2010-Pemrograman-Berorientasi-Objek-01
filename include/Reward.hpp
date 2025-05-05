#ifndef REWARD_H
#define REWARD_H

#include <map>

#include "character.hpp"
#include "inventory.hpp"
#include "item.hpp"
#include "exception.hpp"

class Reward {
   private:
    int exp;
    int gold;
    std::map<Item *, int> items;

   public:
    // ctor default semua atribut 0/kosong
    Reward();
    // dtor, jangan mendealokasikan Item * karena itu diambil langsung dari mobloot
    // takut saat membuat monster baru gaada lootnya??
    ~Reward();
    // cctor dan assignment dilakukan otomatis oleh compiler

    // Getter
    int getExp() const;
    int getGold() const;
    std::map<Item *, int> getItems() const;

    // Manipulasi atribut
    void addExp(int);
    void addGold(int);
    void addItem(Item *, int);

    /*
     * Format:
     * Current Reward
     * Exp: <exp>
     * Gold: <Gold>
     * Items:
     *     <no>. <count> <item name>
     *     1. 20 Item1
     *     2. 10 Item2
     */
    void displayInfo();

    // Memberikan prize kepada char dan player
    void giveTo(Character*, Inventory*);

    // Memberikan prize HANYA ITEM kepada player (kasus special dungeon)
    void giveTo(Inventory*);

    // Helper menambahkan exp ke character
    void addExpToCharacter(Character* c, int exp);

    // Helper menambahkan gold ke character
    void addGoldToCharacter(Character* c, int gold);
};

#endif