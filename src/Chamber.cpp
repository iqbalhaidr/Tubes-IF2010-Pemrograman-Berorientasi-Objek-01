#include <iostream>

#include "../include/Chamber.hpp"

Chamber::Chamber(bool isLast, int minMobLevel, int maxMobLevel) : isLastChamber(isLast), minMobLevel(minMobLevel), maxMobLevel(maxMobLevel) {
    rewardExp = generateRewardExp();
    rewardGold = generateRewardGold();
    generateEnemies();
}

Chamber::Chamber(const Chamber& c) {
    this->rewardExp = c.rewardExp;
    this->rewardGold = c.rewardGold;
    this->enemyCount = c.enemyCount;
    this->enemies = c.enemies;
    this->isLastChamber = c.isLastChamber;
    this->minMobLevel = c.minMobLevel;
    this->maxMobLevel = c.maxMobLevel;
}

Chamber::~Chamber() {
    for (int i = 0; i < enemyCount; i++) {
        delete enemies[i];
    }
    enemies.clear();
}

Chamber& Chamber::operator=(const Chamber& c) {
    this->rewardExp = c.rewardExp;
    this->rewardGold = c.rewardGold;
    this->enemyCount = c.enemyCount;
    this->enemies = c.enemies;
    this->isLastChamber = c.isLastChamber;
    this->minMobLevel = c.minMobLevel;
    this->maxMobLevel = c.maxMobLevel;
    return *this;
}

int Chamber::getRewardExp() const { return rewardExp; }
int Chamber::getRewardGold() const { return rewardGold; }
int Chamber::getEnemyCount() const { return enemyCount; }
std::vector<Mobs *> Chamber::getEnemies() const { return enemies; }
int Chamber::isLast() const { return isLastChamber; }
int Chamber::getMinMobLevel() const { return rewardExp; }
int Chamber::getMaxMobLevel() const { return rewardGold; }

// void Chamber::setRewardExp(int rewardExp) { this->rewardExp = rewardExp; } 
// void Chamber::setRewardGold(int rewardGold) { this->rewardGold = rewardGold; }
// void Chamber::setEnemyCount(int enemyCount) { this->enemyCount = enemyCount; }
// void Chamber::setLast(bool isLast) { this->isLastChamber = isLast; }

int Chamber::generateRewardGold() {
    int a = 2;
    int b = 3;
    int c = 1;
    return a * minMobLevel + b * maxMobLevel + c * (maxMobLevel - minMobLevel);
}

int Chamber::generateRewardExp() {
    int a = 4;
    int b = 6;
    int c = 2;
    return a * minMobLevel + b * maxMobLevel + c * (maxMobLevel - minMobLevel);
}

int Chamber::generateEnemyCount() {
    if (isLastChamber) {
        return Randomizer::random(MIN_ENEMIES_LAST_CHAMBER, MAX_ENEMIES_LAST_CHAMBER);
    } else {
        return Randomizer::random(MIN_ENEMIES_CHAMBER, MAX_ENEMIES_CHAMBER);
    }
}

BasicMobs* Chamber::generateBasicMobs(int level) {
    switch (Randomizer::random(1, 4)) {
        case 1:
            // return new Slime(level)
        case 2:
            // return new Goblin(level)
        case 3:
            // return new Skeleton(level)
        case 4:
            // return new Orc(level)
        default:
            return nullptr;
    }
}

BossMobs* Chamber::generateBossMobs(int level) {
    switch (Randomizer::random(1, 4)) {
        case 1:
            return new Ogre(level);
        case 2:
            return new DarkKnight(level);
        case 3:
            return new DemonLord(level);
        case 4:
            return new Lich(level);
        default:
            return nullptr;
    }
}

void Chamber::generateEnemies() {
    for (int i = 0; i < enemyCount; i++) {
        delete enemies[i];
    }
    enemies.clear();

    bool isBossSpawnedInBasicChamber = false;
    enemyCount = generateEnemyCount();
    for (int i = 0; i < enemyCount; i++) {
        if (isLastChamber) {
            int level = Randomizer::random(minMobLevel, maxMobLevel);
            enemies.push_back(generateBossMobs(level));
        } else {
            if (!isBossSpawnedInBasicChamber) {
                if (Randomizer::random(1, 5) == 3) { // Asumsi chance boss spawn 20% pada chamber bukan terakhir
                    int level = Randomizer::random(minMobLevel, maxMobLevel);
                    enemies.push_back(generateBossMobs(level));
                    isBossSpawnedInBasicChamber = true;
                } else {
                    int level = Randomizer::random(minMobLevel, maxMobLevel);
                    enemies.push_back(generateBasicMobs(level));
                }
            } else {
                int level = Randomizer::random(minMobLevel, maxMobLevel);
                enemies.push_back(generateBasicMobs(level));
            }
        }
    }
}

/* 
bool battle(Char&, Reward&) {
    for (int i = 0; i < enemyCount; i++) {
        bool isCharTurn = true;
        while (enemies[i]->getHealth() > 0 && Char.getCurrentHealth() > 0) {
            if (isCharTurn) {
                Char.applyTurnbasedEffect();
                if (Char.isStunned()) {
                    Char.decrementTurnRemainingEffect();
                    isCharTurn = !isCharTurn
                    continue;
                }
                int opt = inputOption();
                if (opt == attack) {
                    Char.attack(*enemies[i]);
                } else if (opt == skill) {
                    Char.useSkill(*enemies[i]);
                } else if (opt == item) {
                    Char.useItem(*enemies[i]);
                } else if (opt == item) {
                    return false;
                }
                Char.decrementTurnRemainingEffect();
            } else {
                enemies[i]->applyTurnbasedEffect();
                if (enemies[i]->isStunned()) {
                    enemies[i]->decrementTurnRemainingEffect();
                    isCharTurn = !isCharTurn
                    continue;
                }
                int opt = Randomizer::random(1, 2);
                if (opt == 1) {
                    enemies[i]->attack(Char);
                } else if (opt == 2) {
                    enemies[i]->useSkill(Char);
                }
                enemies[i]->decrementTurnRemainingEffect();
            }
            isCharTurn = !isCharTurn;
        }
        
        if (Char.getCurrentHealth() <= 0) {
            return false;
        }
        
        if (enemies[i]->getCurrentHealth() <= 0) {
            Reward.addExp(enemies[i]->getExpReward())
            Reward.addItem(enemies[i]->getLootItem())
        }
    }
    Reward.addExp(rewardExp);
    Reward.addGold(rewardGold);
    Char.reset()
    return true;
}
 */

void Chamber::displayInfo() {
    std::cout << "Reward Exp: " << rewardExp << std::endl;
    std::cout << "Reward Gold: " << rewardGold << std::endl;
    std::cout << "Enemy Count: " << enemyCount << std::endl;
    std::cout << "Last Chamber: " << isLastChamber << std::endl;
    std::cout << "minMobLevel: " << minMobLevel << std::endl;
    std::cout << "maxMobLevel: " << maxMobLevel << std::endl;
    std::cout << "Enemies: " << std::endl;
    for (int i = 0; i < enemyCount; i++) {
        std::cout << "============================" << std::endl;
        enemies[i]->displayInfo();
    }
}