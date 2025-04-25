#ifndef PRIZE_H
#define PRIZE_H

#include <map>

#include "inventory.hpp"
#include "item.hpp"
// #include "char.hpp"

class Prize {
   private:
    int exp;
    int gold;
    std::map<Item *, int> items;

   public:
    // ctor default semua atribut 0/kosong
    Prize();
    // dtor, mendealokasikan Item*
    ~Prize();
    // cctor dan assignment dilakukan otomatis oleh compiler

    // Getter
    int getExp();
    int getGold();
    std::vector<Item *> getItems();

    // Manipulasi atribut
    void addExp(int gold);
    void addGold(int exp);
    void addItem(Item *);

    /*
     * Format:
     * Current Prize
     * Exp: <exp>
     * Gold: <Gold>
     * Items:
     *     <no>. <count> <item name>
     *     1. 20 Item1
     *     2. 10 Item2
     */
    void displayInfo();

    // Memberikan prize kepada char dan player
    // void giveTo(Char &, Inventory &);
};

#endif