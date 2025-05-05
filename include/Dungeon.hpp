#ifndef DUNGEON_H
#define DUNGEON_H

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include "Chamber.hpp"
#include "Randomizer.hpp"
#include "Reward.hpp"
#include "character.hpp"
#include "items.hpp"
#include "animation.hpp"

class Dungeon {
   private:
    int totalChambers;
    std::vector<Chamber *> chambers;
    int rewardExp;
    int rewardGold;
    Item *bonusItem;
    bool isDD;
    Reward prize;
    int penaltyExp;
    int penaltyGold;
    string rank;
    int minLevel;
    int entryCost;

   public:
    Dungeon(string rank, Mobloot &mobLoots, Items &items, Character &c);
    ~Dungeon();
    // Dungeon(const Dungeon &);
    // Dungeon &operator=(const Dungeon &);
    // cctor dan = jangan dipake, selalu buat baru

    // Getter

    // Setter

    void start(Character &, Inventory &, Items &);

    /* Randomize, set isDD, update reward */
    void randomizeDoubleDungeon();

    /* Setter attribute based on rank */
    void helperSet(Items &, Character &);

    /* Generate chambers berdasarkan rank, set totalChambers */
    void generateChambers(Mobloot &);

    void displayInfo();

    /* Helper pemberi penalty */
    void substractExp(Character *, int);

    void substractGold(Character *, int);

    /* Fungsi simulasi type effect */
    void typeEffect(const std::string &text, int delayMs = 50);

    /* Fungsi menampilkan message lore awal masuk dungeon */
    void welcomeMessage();

    /* Fungsi menampilkan message kemenangan */
    void winningMessage();

    /* Fungsi menampilkan message kekalahan */
    void losingMessage();
};

#endif