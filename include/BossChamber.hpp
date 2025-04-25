#ifndef BOSSCHAMBER_H
#define BOSSCHAMBER_H

#define BOSSMOB_POOL 5

// #include "BossMobs.hpp"
#include <vector>

#include "Chamber.hpp"
#include "Prize.hpp"

class BossChamber : public Chamber {
   private:
    int enemyCount;  // Simpan data banyak musuh
    // std::vector<BossMobs *> enemies; // List musuh yang harus dilawan
   public:
    // 4 Sekawan
    BossChamber();
    BossChamber(int rewardExp, int rewardGold, int difficultyScaling,
                int enemyCount);
    BossChamber(const BossChamber&);
    // Mendealokasikan BossMobs *
    ~BossChamber();
    BossChamber& operator=(const BossChamber&);

    // Getter
    int getEnemyCount();
    // std::vector<BossMobs *> getEnemies();

    // Setter
    void setEnemyCount(int);

    // Generate random BossMob sebanyak <enemyCount> lalu simpan di <enemies>
    // Spek monster sesuai difficulty scaling
    void generateEnemies();

    // Main function battle, jika menang return true dan sebaliknya
    // bool battle(Char&, Prize&);

    /*
     * Format:
     * Enemies List (BossChamber):
     * <seq_no>. <name of bossmobs> <strength> <agility> <intelligence>
     * 1. Ogre 10 20 30
     * 2. Dark Knight 40 50 60
     */
    void displayInfo();
};

#endif