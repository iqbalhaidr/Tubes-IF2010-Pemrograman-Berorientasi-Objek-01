#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>

#include "Chamber.hpp"
#include "Reward.hpp"
// #include "Char.hpp"
#include "Randomizer.hpp"

class Dungeon {
   private:
    int totalChambers;
    std::vector<Chamber *> chambers;
    int rewardExp;
    int rewardGold;
    Item *bonusItem;  // KALO DOUBLE DUNGEON TIDAK 3x KAH?
    bool isDD;        // Double Dungeon
    Reward prize;
    int penaltyExp;
    int penaltyGold;
    string rank;
    int minLevel;
    int entryCost;

   public:
    Dungeon(string rank);
    ~Dungeon();
    // Dungeon(const Dungeon &);
    // Dungeon &operator=(const Dungeon &);
    // cctor dan = jangan dipake, selalu buat baru

    // Getter

    // Setter

    // void start(Char&, Inventory&);

    /* Randomize, set isDD, update reward */
    void randomizeDoubleDungeon();

    /* Setter attribute based on rank */
    void helperSet();

    /* Generate chambers berdasarkan rank, set totalChambers */
    void generateChambers();
};

#endif