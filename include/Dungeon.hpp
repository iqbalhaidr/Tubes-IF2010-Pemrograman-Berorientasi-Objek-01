#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>

#include "Chamber.hpp"
#include "Prize.hpp"
#include "inventory.hpp"
#include "item.hpp"
// #include "Char.hpp"

class Dungeon {
   private:
    int totalChambers;
    std::vector<Chamber *> chambers;
    int rewardExp;
    int rewardGold;
    Item *bonusItem;
    bool isDD;  // Double Dungeon
    Prize prize;
    int difficultyScaling;
    int penaltyExp;
    int penaltyGold;

   public:
    Dungeon(int totalChambers, int rewardExp, int rewardGold, bool isDD);
    Dungeon(const Dungeon &);
    ~Dungeon();
    Dungeon &operator=(const Dungeon &);

    // Getter

    // Setter

    // void start(Char&, Inventory&) = 0;
};

#endif