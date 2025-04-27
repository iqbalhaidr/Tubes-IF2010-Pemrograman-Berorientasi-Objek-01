#include <iostream>

#include "../include/Chamber.hpp"

// 4 Sekawan
// <enemyCount> di randomize sesuai bound macro
Chamber::Chamber(int rewardExp, int rewardGold, bool isLast, float difficultyScaling) : rewardExp(rewardExp), rewardGold(rewardGold), isLastChamber(isLast) {
    if (isLastChamber) {
        enemyCount = Randomizer::random(MIN_ENEMIES_LAST_CHAMBER, MAX_ENEMIES_LAST_CHAMBER);
    } else {
        enemyCount = Randomizer::random(MIN_ENEMIES_CHAMBER, MAX_ENEMIES_CHAMBER);
    }
    generateEnemies(difficultyScaling);
}

Chamber::Chamber(const Chamber& c) {
    this->rewardExp = c.rewardExp;
    this->rewardGold = c.rewardGold;
    this->enemyCount = c.enemyCount;
    this->enemies = c.enemies;
    this->isLastChamber = c.isLastChamber;
}

// Delete Mobs *
Chamber::~Chamber() {
    std::vector<Mobs *>::iterator i = enemies.begin();
    for (; i != enemies.end(); i++) {
        delete *i;
    }
    enemies.clear();
}

Chamber& Chamber::operator=(const Chamber& c) {
    this->rewardExp = c.rewardExp;
    this->rewardGold = c.rewardGold;
    this->enemyCount = c.enemyCount;
    this->enemies = c.enemies;
    this->isLastChamber = c.isLastChamber;
}

// Getter
int Chamber::getRewardExp() const { return rewardExp; }
int Chamber::getRewardGold() const { return rewardGold; }
int Chamber::getEnemyCount() const { return enemyCount; }
std::vector<Mobs *> Chamber::getEnemies() const { return enemies; }
int Chamber::isLast() const { return isLastChamber; }

// Setter
void Chamber::setRewardExp(int rewardExp) { this->rewardExp = rewardExp; } 
void Chamber::setRewardGold(int rewardGold) { this->rewardGold = rewardGold; }
void Chamber::setEnemyCount(int enemyCount) { this->enemyCount = enemyCount; }
void Chamber::setLast(bool isLast) { this->isLastChamber = isLast; }

/*
 * Mengisi <enemies> dengan <Mobs *> sebanyak <enemyCount>
 * <Mobs> memiliki stats sesuai dengan <difficultyScaling>
 * Apabila last chamber maka harus diisi BossMobs
 * [Sementara non last chamber tidak mungkin boss]
 * Apabila bukan last chamber ada kemungkinan salah satu enemies
 * diisi BossMobs maksimal 1 sesuai dengan macro chance
 */
void Chamber::generateEnemies(float difficultyScaling) {
    std::vector<Mobs *>::iterator i = enemies.begin();
    for (; i != enemies.end(); i++) {
        delete *i;
    }
    enemies.clear();

    for (int i = 0; i < enemyCount; i++) {
        int finalDifficulty = difficultyScaling + i * 0.05f;
        if (isLastChamber) {
            switch (Randomizer::random(1, 4)) {
                case 1:
                    // enemies.push_back(new BossMob1(<finalDifficulty>))
                    break;
                case 2:
                    // enemies.push_back(new BossMob2(<finalDifficulty>))
                    break;
                case 3:
                    // enemies.push_back(new BossMob3(<finalDifficulty>))
                    break;
                case 4:
                    // enemies.push_back(new BossMob4(<finalDifficulty>))
                    break;
            }
        } else {
            switch (Randomizer::random(1, 4)) {
                case 1:
                    // enemies.push_back(new BasicMob1(<finalDifficulty>))
                    break;
                case 2:
                    // enemies.push_back(new BasicMob2(<finalDifficulty>))
                    break;
                case 3:
                    // enemies.push_back(new BasicMob3(<finalDifficulty>))
                    break;
                case 4:
                    // enemies.push_back(new BasicMob4(<finalDifficulty>))
                    break;
            }
        }
    }
}

/*
 * Mengembalikan true jika berhasil membunuh semua enemy
 * Mengembalikan false jika kabur atau mati
 * Sistem turn based dengan musuh sequential
 * Mereset effect, health, mana setelah keluar battle
 */
/* 
bool battle(Char&, Reward&) {
    for (int i = 0; i < enemyCount; i++) {
        bool isCharTurn = true;
        while (enemies[i]->getHealth() > 0 && enemies) {
            // Parse effect
            if (isCharTurn) {
                // Choose Option
            } else {
                // Randomize Option
            }
            // Update effect

        }
    }


}





 */

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
void Chamber::displayInfo() {
    std::cout << "Reward Exp: " << rewardExp << std::endl;
    std::cout << "Reward Gold: " << rewardGold << std::endl;
    std::cout << "Enemy Count: " << enemyCount << std::endl;\
    std::cout << "Last Chamber: ";
    if (isLastChamber) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }
    std::cout << "Enemies: " << std::endl;
    for (int i = 0; i < enemyCount; i++) {
        std::cout << i + 1 << ". " << enemies[i]->getName() << " " 
        << enemies[i]->getStats().getStrength() << " " 
        << enemies[i]->getStats().getAgility() << " " 
        << enemies[i]->getStats().getIntelligence() << std::endl;
    }
}