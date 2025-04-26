#ifndef REWARD_H
#define REWARD_H

#include <map>

#include "inventory.hpp"
#include "item.hpp"
// #include "char.hpp"

class Reward {
   private:
    int exp;
    int gold;
    std::map<Item *, int> items;

   public:
    // ctor default semua atribut 0/kosong
    Reward();
    // dtor, mendealokasikan Item*
    ~Reward();
    // cctor dan assignment dilakukan otomatis oleh compiler

    // Getter
    int getExp() const;
    int getGold() const;
    std::vector<Item *> getItems() const;

    // Manipulasi atribut
    void addExp(int gold);
    void addGold(int exp);
    void addItem(Item *);

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
    // void giveTo(Char &, Inventory &);
};

#endif