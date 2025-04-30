#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>

#include "Chamber.hpp"
#include "Reward.hpp"
#include "character.hpp"
#include "Randomizer.hpp"
#include "items.hpp"

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
    Dungeon(string rank, Mobloot &mobLoots, Items &items);
    ~Dungeon();
    // Dungeon(const Dungeon &);
    // Dungeon &operator=(const Dungeon &);
    // cctor dan = jangan dipake, selalu buat baru

    // Getter

    // Setter

    void start(Character&, Inventory&, Items&);

    /* Randomize, set isDD, update reward */
    void randomizeDoubleDungeon();

    /* Setter attribute based on rank */
    void helperSet(Items&);

    /* Generate chambers berdasarkan rank, set totalChambers */
    void generateChambers(Mobloot&);

    void displayInfo();

    /* Helper pemberi penalty */
    void substractExp(Character*, int);

    void substractGold(Character*, int);
};

#endif