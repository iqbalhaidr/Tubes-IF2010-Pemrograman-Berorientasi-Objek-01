#ifndef BOSSCHAMBER_H
#define BOSSCHAMBER_H

#define BASICMOB_POOL 5

// #include "BasicMobs.hpp"
#include <vector>

#include "Chamber.hpp"
#include "Prize.hpp"

class BasicChamber : public Chamber {
   private:
    int enemyCount;  // Simpan data banyak musuh
    // std::vector<BasicMobs *> enemies; // List musuh yang harus dilawan
   public:
    // 4 Sekawan
    BasicChamber();
    BasicChamber(int rewardExp, int rewardGold, int difficultyScaling,
                 int enemyCount);
    BasicChamber(const BasicChamber&);
    // Mendealokasikan BossMobs *
    ~BasicChamber();
    BasicChamber& operator=(const BasicChamber&);

    // Getter
    int getEnemyCount();
    // std::vector<BossMobs *> getEnemies();

    // Setter
    void setEnemyCount(int);

    // Generate random BasicMob sebanyak <enemyCount> lalu simpan di <enemies>
    // Spek monster sesuai difficulty scaling
    void generateEnemies();

    // Main function battle, jika menang return true dan sebaliknya
    // bool battle(Char&, Prize&);

    /*
     * Format:
     * Enemies List (BasicChamber):
     * <seq_no>. <name of basicmobs> <strength> <agility> <intelligence>
     * 1. Slime 10 20 30
     * 2. Goblin 40 50 60
     */
    void displayInfo();
};

#endif