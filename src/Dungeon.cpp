#include "../include/Dungeon.hpp"
#include <iostream>

Dungeon::Dungeon(string rank, Mobloot &mobLoots, Items &items) : prize() {
    this->rank = rank;
    this->penaltyExp = 100; // Tiap rank dibuat penalty sama
    this->penaltyGold = 100;
    helperSet(items);
    randomizeDoubleDungeon();
    generateChambers(mobLoots);
}

Dungeon::~Dungeon() {
    for (Chamber* c : chambers) {
        delete c;
    }
    chambers.clear();

    delete bonusItem;
}

void Dungeon::randomizeDoubleDungeon() {
    if (Randomizer::random(1, 5) == 1) {
        std::cout << "TERJADI DOUBLE DUNGEON!" << std::endl;
        isDD = true;
        rewardExp *= 3;
        rewardGold *= 3;
    } else {
        isDD = false;
    }
}

void Dungeon::helperSet(Items &items) {
    if (rank == "S") {
        minLevel = 50;
        entryCost = 1000;
        rewardExp = 600;
        rewardGold = 600;
        // bonusItem = items.getItem("ItemS");
    } else if (rank == "A") {
        minLevel = 35;
        entryCost = 500;
        rewardExp = 500;
        rewardGold = 500;
        // bonusItem = items.getItem("ItemA");
    } else if (rank == "B") {
        minLevel = 25;
        entryCost = 300;
        rewardExp = 400;
        rewardGold = 400;
        // bonusItem = items.getItem("ItemB");
    } else if (rank == "C") {
        minLevel = 20;
        entryCost = 150;
        rewardExp = 300;
        rewardGold = 300;
        // bonusItem = items.getItem("ItemC");
    } else if (rank == "D") {
        minLevel = 10;
        entryCost = 0;
        rewardExp = 200;
        rewardGold = 200;
        // bonusItem = items.getItem("ItemD");
    } else if (rank == "E") {
        minLevel = 0;
        entryCost = 0;
        rewardExp = 100;
        rewardGold = 100;
        bonusItem = items.getItem("EXC");
    } else if (rank == "SPECIAL") {
        minLevel = 0;
        entryCost = 0;
        rewardExp = 1000;
        rewardGold = 1000;
        // bonusItem = items.getItem("ItemSPECIAL");
    }
}

void Dungeon::generateChambers(Mobloot &mobLoots) {
    if (rank == "S") {
        totalChambers = 6;
        int minMobLevel = isDD ? 100 : 50;
        int maxMobLevel = isDD ? 200 : 100;

        for (int i = 0; i < totalChambers - 1; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel, mobLoots));
        }
        chambers.push_back(new Chamber(true, minMobLevel, maxMobLevel, mobLoots));
    } else if (rank == "A") {
        totalChambers = 5;
        int minMobLevel = isDD ? 60 : 30;
        int maxMobLevel = isDD ? 140 : 70;

        for (int i = 0; i < totalChambers - 1; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel, mobLoots));
        }
        chambers.push_back(new Chamber(true, minMobLevel, maxMobLevel, mobLoots));
    } else if (rank == "B") {
        totalChambers = 4;
        int minMobLevel = isDD ? 40 : 20;
        int maxMobLevel = isDD ? 100 : 50;

        for (int i = 0; i < totalChambers - 1; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel, mobLoots));
        }
        chambers.push_back(new Chamber(true, minMobLevel, maxMobLevel, mobLoots));
    } else if (rank == "C") {
        totalChambers = 3;
        int minMobLevel = isDD ? 20 : 10;
        int maxMobLevel = isDD ? 70 : 35;

        for (int i = 0; i < totalChambers - 1; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel, mobLoots));
        }
        chambers.push_back(new Chamber(true, minMobLevel, maxMobLevel, mobLoots));
    } else if (rank == "D") {
        totalChambers = 2;
        int minMobLevel = isDD ? 0 : 0;
        int maxMobLevel = isDD ? 50 : 25;

        for (int i = 0; i < totalChambers; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel, mobLoots));
        }
    } else if (rank == "E") {
        totalChambers = 1;
        int minMobLevel = isDD ? 0 : 0;
        int maxMobLevel = isDD ? 20 : 10;

        // std::cout << "Check2 Dungeon.cpp\n";
        for (int i = 0; i < totalChambers; i++) {
            // std::cout << "Check3 Dungeon.cpp\n";
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel, mobLoots));
            // std::cout << minMobLevel<<" MINIMAL LEVEL E \n";
            // std::cout << maxMobLevel<<" MAXIMAL LEVEL E \n";
        }
    } else if (rank == "SPECIAL") {
        totalChambers = 100;

        for (int i = 0; i < totalChambers - 1; i++) {
            int curLevel = isDD ? (i + 1) * 2 : (i + 1);
            chambers.push_back(new Chamber(false, curLevel, curLevel, mobLoots));
        }
        int curLevel = isDD ? 200 : 100;
        chambers.push_back(new Chamber(true, 100, 100, mobLoots));
    }
}

void Dungeon::start(Character &c, Inventory &inv, Items &items) {
    bool neverLose = true;
    int ctr = 0;

    while (neverLose && ctr < totalChambers) {
        bool result = chambers[ctr]->battle(c, inv, this->prize, items);
        neverLose = result;
        ctr++;
    }

    if (neverLose) {
        std::cout << "SELAMAT BERHASIL MENYELESAIKAN DUNGEON" << std::endl;
        prize.addExp(rewardExp);
        prize.addGold(rewardGold);
        prize.addItem(bonusItem, 1);
        prize.giveTo(&c, &inv);
    } else {
        std::cout << "GAGAL MENYELESAIKAN DUNGEON" << std::endl;
        substractExp(&c, penaltyExp);
        substractGold(&c, penaltyGold);
        if (isDD) {
            prize.giveTo(&inv);
        }
    }

    std::cout << "SAMPAI JUMPA LAGI!" << std::endl;
    c.reset();
}

void Dungeon::displayInfo()  {
    std::cout << "Dungeon Rank: " << rank << std::endl;
    std::cout << "Total Chambers: " << totalChambers << std::endl;
    std::cout << "Entry Cost: " << entryCost << std::endl;
    std::cout << "Minimum Level: " << minLevel << std::endl;
    std::cout << "Reward Exp: " << rewardExp << std::endl;
    std::cout << "Reward Gold: " << rewardGold << std::endl;
    std::cout << "isDD: " << (isDD ? "Yes" : "No") << std::endl;
    std::cout << "Penalty Exp: " << penaltyExp << std::endl;
    std::cout << "Penalty Gold: " << penaltyGold << std::endl;
    std::cout << "Prize: " << std::endl;
    prize.displayInfo();
    std::cout << "Bonus Item: " << (bonusItem ? bonusItem->getName() : "None") << std::endl;
    std::cout << "Chambers:" << std::endl;
    for (int i = 0; i < totalChambers; ++i) {
        std::cout << "  Chamber " << i + 1 << ":" << std::endl;
        chambers[i]->displayInfo();
    }
}

void Dungeon::substractExp(Character *c, int penaltyExp) {
    if (penaltyExp > c->getExp()) {
        penaltyExp = c->getExp();
    }
    c->setExp(c->getExp() - penaltyExp);
}

void Dungeon::substractGold(Character *c, int penaltyGold) {
    if (penaltyGold > c->getGold()) {
        penaltyGold = c->getGold();
    }
    c->setGold(c->getGold() - penaltyGold);
}