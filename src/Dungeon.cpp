#include "../include/Dungeon.hpp"
#include <iostream>

Dungeon::Dungeon(string rank) : prize() {
    this->rank = rank;
    this->penaltyExp = 100; // Tiap rank dibuat penalty sama
    this->penaltyGold = 100;
    helperSet();
    randomizeDoubleDungeon();
    generateChambers();
}

Dungeon::~Dungeon() {
    for (Chamber* c : chambers) {
        delete c;
    }
    chambers.clear();

    delete bonusItem;
}

void Dungeon::randomizeDoubleDungeon() {
    if (Randomizer::random(1, 2) == 1) {
        std::cout << "TERJADI DOUBLE DUNGEON!" << std::endl;
        isDD = true;
        rewardExp *= 3;
        rewardGold *= 3;
    } else {
        isDD = false;
    }
}

void Dungeon::helperSet() {
    if (rank == "S") {
        minLevel = 50;
        entryCost = 1000;
        // totalChambers = 6;
        rewardExp = 600;
        rewardGold = 600;
        // bonusItem = new Item(ITEM_S); GW GATAU INI IMPLEMENTASINYA GIMANA
    } else if (rank == "A") {
        minLevel = 35;
        entryCost = 500;
        // totalChambers = 5;
        rewardExp = 500;
        rewardGold = 500;
        // bonusItem = new Item(ITEM_A); GW GATAU INI IMPLEMENTASINYA GIMANA
    } else if (rank == "B") {
        minLevel = 25;
        entryCost = 300;
        // totalChambers = 4;
        rewardExp = 400;
        rewardGold = 400;
        // bonusItem = new Item(ITEM_B); GW GATAU INI IMPLEMENTASINYA GIMANA
    } else if (rank == "C") {
        minLevel = 20;
        entryCost = 150;
        // totalChambers = 3;
        rewardExp = 300;
        rewardGold = 300;
        // bonusItem = new Item(ITEM_C); GW GATAU INI IMPLEMENTASINYA GIMANA
    } else if (rank == "D") {
        minLevel = 10;
        entryCost = 0;
        // totalChambers = 2;
        rewardExp = 200;
        rewardGold = 200;
        // bonusItem = new Item(ITEM_D); GW GATAU INI IMPLEMENTASINYA GIMANA
    } else if (rank == "E") {
        minLevel = 0;
        entryCost = 0;
        // totalChambers = 1;
        rewardExp = 100;
        rewardGold = 100;
        // bonusItem = new Item(ITEM_E); GW GATAU INI IMPLEMENTASINYA GIMANA
    } else if (rank == "SPECIAL") {
        minLevel = 0;
        entryCost = 0;
        // totalChambers = 100;
        rewardExp = 1000;
        rewardGold = 1000;
        // bonusItem = new Item(ITEM_SPECIAL); GW GATAU INI IMPLEMENTASINYA GIMANA
    }
}

void Dungeon::generateChambers() {
    if (rank == "S") {
        totalChambers = 6;
        int minMobLevel = isDD ? 100 : 50;
        int maxMobLevel = isDD ? 200 : 100;

        for (int i = 0; i < totalChambers - 1; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel));
        }
        chambers.push_back(new Chamber(true, minMobLevel, maxMobLevel));
    } else if (rank == "A") {
        totalChambers = 5;
        int minMobLevel = isDD ? 60 : 30;
        int maxMobLevel = isDD ? 140 : 70;

        for (int i = 0; i < totalChambers - 1; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel));
        }
        chambers.push_back(new Chamber(true, minMobLevel, maxMobLevel));
    } else if (rank == "B") {
        totalChambers = 4;
        int minMobLevel = isDD ? 40 : 20;
        int maxMobLevel = isDD ? 100 : 50;

        for (int i = 0; i < totalChambers - 1; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel));
        }
        chambers.push_back(new Chamber(true, minMobLevel, maxMobLevel));
    } else if (rank == "C") {
        totalChambers = 3;
        int minMobLevel = isDD ? 20 : 10;
        int maxMobLevel = isDD ? 70 : 35;

        for (int i = 0; i < totalChambers - 1; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel));
        }
        chambers.push_back(new Chamber(true, minMobLevel, maxMobLevel));
    } else if (rank == "D") {
        totalChambers = 2;
        int minMobLevel = isDD ? 0 : 0;
        int maxMobLevel = isDD ? 50 : 25;

        for (int i = 0; i < totalChambers; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel));
        }
    } else if (rank == "E") {
        totalChambers = 1;
        int minMobLevel = isDD ? 0 : 0;
        int maxMobLevel = isDD ? 20 : 10;

        for (int i = 0; i < totalChambers; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel));
        }
    } else if (rank == "SPECIAL") {
        totalChambers = 100;

        for (int i = 0; i < totalChambers - 1; i++) {
            int curLevel = isDD ? (i + 1) * 2 : (i + 1);
            chambers.push_back(new Chamber(false, curLevel, curLevel));
        }
        int curLevel = isDD ? 200 : 100;
        chambers.push_back(new Chamber(true, 100, 100));
    }

    /*
    void start(Char &c, Inventory &inv) {
        bool neverLose = true;
        int ctr = 0

        while (neverLose && ctr < totalChambers) {
            bool result = chambers[ctr]->battle(c, this->prize);
            neverLose = result;
            ctr++
        }

        if (neverLose) {
            std::cout << "SELAMAT BERHASIL MENYELESAIKAN DUNGEON" << std::endl;
            prize.addExp(rewardExp);
            prize.addGold(rewardGold);
            prize.addItem(bonusItem, 1);
            prize.giveTo(c, inv);
        } else {
            std::cout << "GAGAL MENYELESAIKAN DUNGEON" << std::endl;
            c.substractExp(penaltyExp);
            c.substractGold(penaltyGold);
            if (isDD) {
                prize.giveTo(inv&);
            }
        }

        std::cout << "SAMPAI JUMPA LAGI!" << std::endl;
        c.reset();
    }
    */
}
