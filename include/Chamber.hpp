#ifndef CHAMBER_H
#define CHAMBER_H

#define MIN_ENEMIES_LAST_CHAMBER 2
#define MAX_ENEMIES_LAST_CHAMBER 4
#define MIN_ENEMIES_CHAMBER 2
#define MAX_ENEMIES_CHAMBER 4
#define CHANCE_BOSS_NOT_ON_LAST_CHAMBER 0.1f
#define BASE_STATS 100;

#include <string>
#include <vector>

// #include "Char.hpp"
#include "Randomizer.hpp"
#include "Reward.hpp"
#include "mobs.hpp"
#include "basicMobs.hpp"
#include "bossMobs.hpp"
#include "ogre.hpp"
#include "darkKnight.hpp"
#include "demonLord.hpp"
#include "lich.hpp"
// #include "slime.hpp"
// #include "goblin.hpp"
// #include "skeleton.hpp"
// #include "orc.hpp"

class Chamber {
   private:
    int rewardExp;
    int rewardGold;
    int enemyCount;
    std::vector<Mobs *> enemies;
    bool isLastChamber;
    int minMobLevel;
    int maxMobLevel;

    /*
     * Rasionalisasi minMobLevel, maxMobLevel:
     *
     * Stats mobs bergantung pada level
     * Batas level pada setiap rank sudah sesuai difficulty scaling
     * Jika dungeon biasa maka masukan batas level sesuai rank
     * Jika double dungeon cukup x2 batas level
     * Jika special dungeon cukup increment batas level
     *     Misal:
     *     Chamber1 -> batas = [1, 1]
     *     Chamber2 -> batas = [2, 2]
     *     dan seterusnya
     *
     *     Sehingga pada double dungeon
     *     setiap chamber memiliki level monster sama
     */

   public:
    /*
     * Konstruktor
     * [rewardExp, rewardGold] randomize berdasarkan batas mob level
     * [enemyCount] randomize berdasarkan isLastChamber dan macro
     */
    Chamber(bool isLast, int minMobLevel, int maxMobLevel);
    Chamber(const Chamber &);
    // Delete Mobs *
    ~Chamber();
    Chamber &operator=(const Chamber &);

    // Getter
    int getRewardExp() const;
    int getRewardGold() const;
    int getEnemyCount() const;
    std::vector<Mobs *> getEnemies() const;
    int isLast() const;
    int getMinMobLevel() const;
    int getMaxMobLevel() const;

    // Setter (TIDAK BOLEH MENGGANTI-GANTI NILAI ATRIBUT)
    // void setRewardExp(int);
    // void setRewardGold(int);
    // void setEnemyCount(int);
    // void setLast(bool);

    /*
     * Mengisi <enemies> dengan <Mobs *> sebanyak generateEnemyCount()
     * <Mobs> memiliki level dalam batas level mob
     * Apabila last chamber maka harus diisi BossMobs
     * Apabila bukan last chamber ada kemungkinan salah satu enemies
     * diisi BossMobs maksimal 1 sesuai dengan macro chance
     * update nilai enemy count
     */
    void generateEnemies();

    /*
     * Rumus: a * minMobLevel + b * maxMobLevel + c * range
     * a, b, c = faktor pengali
     * range = range level mob
     */
    int generateRewardGold();

    /*
     * Rumus sama seperti generateRewardGold()
     */
    int generateRewardExp();

    /*
     * Randomize jumlah musuh bedasarkan macro
     */
    int generateEnemyCount();

    /*
     * Randomize basic mobs dengan level sesuai, mengembalikan BasicMobs*
     */
    BasicMobs* generateBasicMobs(int level);

    /*
     * Randomize boss mobs dengan level sesuai, mengembalikan BossMobs*
     */
    BossMobs* generateBossMobs(int level);

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
    * Last Chamber: <isLast>
    * minMobLevel: <minMobLevel>
    * maxMobLevel: <maxMobLevel>
    * ============================
    * Enemy <seq_no>: 
    * enemies[i].displayInfo();
    * ============================
    */
    void displayInfo();
};

#endif