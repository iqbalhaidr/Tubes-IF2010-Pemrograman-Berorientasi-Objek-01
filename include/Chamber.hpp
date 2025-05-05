#ifndef CHAMBER_H
#define CHAMBER_H

#define MIN_ENEMIES_LAST_CHAMBER 1
#define MAX_ENEMIES_LAST_CHAMBER 2
#define MIN_ENEMIES_CHAMBER 2
#define MAX_ENEMIES_CHAMBER 4
#define CHANCE_BOSS_NOT_ON_LAST_CHAMBER 0.10f
#define DISPLAY_TIME 3000
#define BIG_DAMAGE 9999

#include <string>
#include <vector>
#include <stdlib.h>
#include <thread>
#include <chrono>

#include "Randomizer.hpp"
#include "Reward.hpp"
#include "basicMobs.hpp"
#include "bossMobs.hpp"
#include "character.hpp"
#include "darkKnight.hpp"
#include "demonLord.hpp"
#include "goblin.hpp"
#include "lich.hpp"
#include "mobloot.hpp"
#include "mobs.hpp"
#include "ogre.hpp"
#include "orc.hpp"
#include "skeleton.hpp"
#include "slime.hpp"

class Chamber {
   private:
    int rewardExp;
    int rewardGold;
    int enemyCount;
    std::vector<Mobs *> enemies;
    bool isLastChamber;
    int minMobLevel;
    int maxMobLevel;
    Mobloot *mobLoots;
    bool autoMenang;
    bool cheatEnemyStun;
    bool cheatDamage;
    bool cheatGod;

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
    Chamber(bool isLast, int minMobLevel, int maxMobLevel, Mobloot &mobLoots);
    Chamber(const Chamber &);
    // Delete Mobs *
    ~Chamber();
    Chamber &operator=(const Chamber &);

    // Getter
    int getRewardExp() const;
    int getRewardGold() const;
    int getEnemyCount() const;
    int isLast() const;
    int getMinMobLevel() const;
    int getMaxMobLevel() const;
    std::vector<Mobs *> getEnemies() const;

    // Setter (TIDAK BOLEH MENGGANTI-GANTI NILAI ATRIBUT) BUAT APA JUGA?
    // void setRewardExp(int);
    // void setRewardGold(int);
    // void setEnemyCount(int);
    // void setLast(bool);

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
    BasicMobs *generateBasicMobs(int level);

    /*
     * Randomize boss mobs dengan level sesuai, mengembalikan BossMobs*
     */
    BossMobs *generateBossMobs(int level);

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
     * Mengembalikan true jika berhasil membunuh semua enemy
     * Mengembalikan false jika kabur atau mati
     * Sistem turn based dengan musuh sequential
     * Mereset effect, health, mana setelah keluar battle
     */
    bool battle(Character &, Inventory &, Reward &, Items &);

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

    /* Fungsi menerima opsi pertarungan */
    int inputOption();

    /* Fungsi membuang efek yang remainingDuration == 0 */
    void removeExpiredEffects(Unit *);

    /* Fungsi memilih skill yang digunakan */
    int inputSkillOption(Unit *);

    // /* Fungsi memilih item yang digunakan */
    // string inputItemOption(Inventory &);

    /* Fungsi helper Opsi Use Item pada battle chamber  */
    void useItemOption(Character &, Inventory &, Items &, Unit &);

    /* Fungsi helper untuk memilih item yang digunakan */
    bool useItemMenu(Character &, Inventory &, Items &, Unit &);

    /* Fungsi helper unequip equipment */
    void unequipMenu(Character &, Unit &, Inventory &);

    /* Fungsi menampilkan status player tiap turn
     * Format:
     * <player name>'s Status
     * Health: <current health>/<max health> | +<health regen>/turn
     * Mana: <current mana>/<max mana> | +<mana regen>/turn
     * Active Effects:
     *    <effect name> -> <remaining duration> turn left
     */
    void displayPlayerStatus(Character &);

    void displayEnemyStatus(Mobs *enemy);

    void displayStatus(Character &, Mobs *);

    void cheatMode(Character &, Reward &);

    void printBar(int , int , const string&);

};

#endif

/*
Enemy: 2/4 | Turn: 10

Player1's Status
Health: 120/150 | +20/turn
Mana: 30/60 | +10/turn
Active Effects:
    Poison -> 10 turn left
  
<enemy>'s Status
Health: <current health>/<max health> | +<health regen>/turn
Mana: <current mana>/<max mana> | +<mana regen>/turn
Active Effects:
    <effect name> -> <remaining duration> turn left

=============================================================

Choose option:
*/
