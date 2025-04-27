#ifndef CHAMBER_H
#define CHAMBER_H

#define MIN_ENEMIES_LAST_CHAMBER 1
#define MAX_ENEMIES_LAST_CHAMBER 2
#define MIN_ENEMIES_CHAMBER 2
#define MAX_ENEMIES_CHAMBER 4
#define CHANCE_BOSS_NOT_ON_LAST_CHAMBER 0.1f
#define BASE_STATS 100;

#include <vector>

#include "IncludeAll.hpp"

class Chamber {
  private:
    int rewardExp;
    int rewardGold;
    int enemyCount;
    std::vector<Mobs *> enemies;
    bool isLastChamber;

   public:
    // 4 Sekawan
    // <enemyCount> di randomize sesuai bound macro
    Chamber(int rewardExp, int rewardGold, bool isLast, float difficultyScaling);
    Chamber(const Chamber&);
    // Delete Mobs *
    ~Chamber();
    Chamber& operator=(const Chamber&);

    // Getter
    int getRewardExp() const;
    int getRewardGold() const;
    int getEnemyCount() const;
    // std::vector<Mobs *> getEnemies() const;
    int isLast() const;

    // Setter
    void setRewardExp(int);
    void setRewardGold(int);
    void setEnemyCount(int);
    void setLast(bool);

    /*
     * Mengisi <enemies> dengan <Mobs *> sebanyak <enemyCount>
     * <Mobs> memiliki stats sesuai dengan <difficultyScaling>
     * Apabila last chamber maka harus diisi BossMobs
     * Apabila bukan last chamber ada kemungkinan salah satu enemies
     * diisi BossMobs maksimal 1 sesuai dengan macro chance
     */
    void generateEnemies(float difficultyScaling);

    /*
     * Mengembalikan true jika berhasil membunuh semua enemy
     * Mengembalikan false jika kabur atau mati
     * Sistem turn based dengan musuh sequential
     * Mereset effect, health, mana setelah keluar battle
     */
    // bool battle(Char&, Reward&);

    /*
     * Format:
     * Reward Exp: <rewardExp>
     * Reward Gold: <rewardGold>
     * Enemy Count: <enemyCount>
     * Last Chamber: <Yes/No>
     * Enemies :
     * <seq_no>. <Basic/Boss> <name of bossmobs> <strength> <agility>
     * <intelligence>
     * 1. [Boss] Ogre 10 20 30
     * 2. [Boss] Dark Knight 40 50 60
     * 3. [Basic] Slime 10 10 10
     */
    void displayInfo();
};

#endif