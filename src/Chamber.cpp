#include "../include/Chamber.hpp"

#include <iostream>

Chamber::Chamber(bool isLast, int minMobLevel, int maxMobLevel, Mobloot& mobLoots)
    : isLastChamber(isLast), minMobLevel(minMobLevel), maxMobLevel(maxMobLevel), mobLoots(&mobLoots) {
    rewardExp = generateRewardExp();
    rewardGold = generateRewardGold();
    generateEnemies();
}

Chamber::Chamber(const Chamber& c) {
    this->rewardExp = c.rewardExp;
    this->rewardGold = c.rewardGold;
    this->enemyCount = c.enemyCount;
    this->isLastChamber = c.isLastChamber;
    this->minMobLevel = c.minMobLevel;
    this->maxMobLevel = c.maxMobLevel;
    this->mobLoots = c.mobLoots;

    this->enemies = c.enemies;
    // TODO: buat clone(). ntah virtual atau pure virtual
    // for (int i = 0; i < enemies.size(); i++) {
    //     this->enemies.push_back(c.enemies[i]->clone());
    // }
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
    this->isLastChamber = c.isLastChamber;
    this->minMobLevel = c.minMobLevel;
    this->maxMobLevel = c.maxMobLevel;
    this->mobLoots = c.mobLoots;

    this->enemies = c.enemies;
    // TODO: buat clone(). ntah virtual atau pure virtual
    // for (int i = 0; i < enemies.size(); i++) {
    //     this->enemies.push_back(c.enemies[i]->clone());
    // }

    return *this;
}

int Chamber::getRewardExp() const { return rewardExp; }
int Chamber::getRewardGold() const { return rewardGold; }
int Chamber::getEnemyCount() const { return enemyCount; }
int Chamber::isLast() const { return isLastChamber; }
int Chamber::getMinMobLevel() const { return minMobLevel; }
int Chamber::getMaxMobLevel() const { return maxMobLevel; }
std::vector<Mobs*> Chamber::getEnemies() const {
    return enemies;

    // TODO: buat clone(). ntah virtual atau pure virtual
    // std::vector<Mobs*> enemiesClone;
    // for (int i = 0; i < enemies.size(); i++) {
    //     enemiesClone.push_back(enemies[i]->clone());
    // }
    // return enemiesClone;
}

// void Chamber::setRewardExp(int rewardExp) { this->rewardExp = rewardExp; }
// void Chamber::setRewardGold(int rewardGold) { this->rewardGold = rewardGold;
// } void Chamber::setEnemyCount(int enemyCount) { this->enemyCount =
// enemyCount; } void Chamber::setLast(bool isLast) { this->isLastChamber =
// isLast; }

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
    int expReward = 100 * level;
    switch (Randomizer::random(1, 4)) {
        case 1:
            return new Slime(level, expReward, *mobLoots);
        case 2:
            return new Goblin(level, expReward, *mobLoots);
        case 3:
            return new Skeleton(level, expReward, *mobLoots);
        case 4:
            return new Orc(level, expReward, *mobLoots);
        default:
            return nullptr;
    }
}

BossMobs* Chamber::generateBossMobs(int level) {
    int expReward = 200 * level;
    switch (Randomizer::random(1, 4)) {
        case 1:
            return new Ogre(level, expReward, *mobLoots);
        case 2:
            return new DarkKnight(level, expReward, *mobLoots);
        case 3:
            return new DemonLord(level, expReward, *mobLoots);
        case 4:
            return new Lich(level, expReward, *mobLoots);
        default:
            return nullptr;
    }
}

void Chamber::generateEnemies() {
    // std::cout << "Check1A Chamber.cpp\n";
    // std::cout << enemyCount << "\n";
    // for (int i = 0; i < enemyCount; i++) {
    //     // std::cout << "Check1AA Chamber.cpp\n";
    //     // delete enemies[i];
    //     // std::cout << "Check1AB Chamber.cpp\n";
    // }
    // enemies.clear();
    // std::cout << "Check1B Chamber.cpp\n";

    bool isBossSpawnedInBasicChamber = false;
    enemyCount = generateEnemyCount();
    for (int i = 0; i < enemyCount; i++) {
        if (isLastChamber) {
            int level = Randomizer::random(minMobLevel, maxMobLevel);
            // std::cout << level << "INI LEVEL BOS JING\n";
            enemies.push_back(generateBossMobs(level));
        } else {
            if (!isBossSpawnedInBasicChamber) {
                if (Randomizer::chance(CHANCE_BOSS_NOT_ON_LAST_CHAMBER)) {
                    int level = Randomizer::random(minMobLevel, maxMobLevel);
                    enemies.push_back(generateBossMobs(level));
                    isBossSpawnedInBasicChamber = true;
                    // std::cout << level << "INI LEVEL BOS JING\n";
                } else {
                    int level = Randomizer::random(minMobLevel, maxMobLevel);
                    enemies.push_back(generateBasicMobs(level));
                    // std::cout << level << "INI LEVEL BOS JING\n";
                }
            } else {
                int level = Randomizer::random(minMobLevel, maxMobLevel);
                enemies.push_back(generateBasicMobs(level));
                // std::cout << level << "INI LEVEL BOS JING\n";
            }
        }
    }
}

bool Chamber::battle(Character& c, Inventory& inv, Reward& prize, Items& items) {
    for (int i = 0; i < enemyCount; i++) {
        bool isCharTurn = true;
        int turnCtr = 0;
        while (enemies[i]->getCurrentHealth() > 0 && c.getCurrentHealth() > 0) {
            if (isCharTurn) {
                if (c.getTurnEffectStatus("Stun")) {  // Cek apakah ada activeEffect stun
                    std::cout << "Character Terkena Stun! Chamber.cpp\n";
                    c.applyActiveEffect();
                    isCharTurn = !isCharTurn;
                    continue;
                }
                
                c.applyActiveEffect();
                
                // Regen health and mana (hanya dipanggil jika tidak ada efek stun)
                c.heal(c.getHealthRegen());
                c.restoreMana(c.getManaRegen());
                std::cout << "Character regen called\n";
                
                std::cout << "Enemy: " << i << "/" << enemyCount << " | Turn: " << turnCtr << std::endl; 
                std::cout << "\n";
                displayPlayerStatus(c) ;
                std::cout << "\n";
                displayEnemyStatus(enemies[i]);
                std::cout << "\n";
                std::cout << "==============================================\n\n";

                int opt = inputOption();
                if (opt == 1) {
                    c.attack(*enemies[i], inv);
                    std::cout << "\n=============================\n";
                    std::cout << "Character Attack! Chamber.cpp\n";
                    std::cout << "Enemy Status: \n";
                    displayEnemyStatus(enemies[i]);
                    std::cout << "=============================\n";
                } else if (opt == 2) {
                    if (c.getSkills().empty()) {
                        std::cout << "No skills available." << std::endl;
                        continue;
                    }
                    int skillOpt = inputSkillOption(&c);
                    c.useSkill(c.getSkills()[skillOpt - 1], *enemies[i]);
                } else if (opt == 3) {
                    string optItem = inputItemOption(inv);
                    inv.useItem(optItem, c, items);
                } else if (opt == 4) {  // KABUR
                    return false;
                }
                removeExpiredEffects(&c);
                turnCtr++;
            } else {
                std::cout << "Enemy Turn! Chamber.cpp\n";
                if (enemies[i]->getTurnEffectStatus("Stun")) {
                    std::cout << "Enemy Terkena Stun! Chamber.cpp\n";
                    enemies[i]->applyActiveEffect();
                    isCharTurn = !isCharTurn;
                    continue;
                }
                
                enemies[i]->applyActiveEffect();
                
                // Regen health and mana (hanya dipanggil jika tidak ada efek stun)
                enemies[i]->heal(enemies[i]->getHealthRegen());
                enemies[i]->restoreMana(enemies[i]->getManaRegen());
                std::cout << "Enemy regen called\n";

                int opt = Randomizer::random(1, 10);
                if (opt == 1) {
                    enemies[i]->attack(c, inv);
                    std::cout << "\n=============================\n";
                    std::cout << "Enemy Attack! Chamber.cpp\n"; 
                    std::cout << "Character Status: \n";
                    displayPlayerStatus(c);
                    std::cout << "=============================\n";
                } else if (opt > 1) {
                    std::cout << "\n=============================\n";
                    std::cout << "Enemy Use Skill! Chamber.cpp\n";
                    if (c.getSkills().empty()) {
                        std::cout << "No skills available." << std::endl;
                        continue;
                    }
                    int skillOpt = Randomizer::random(0, enemies[i]->getSkills().size() - 1);
                    std::cout << "Enemy uses: " << enemies[i]->getSkills()[skillOpt]->getName() << std::endl;
                    enemies[i]->useSkill(enemies[i]->getSkills()[skillOpt], c);
                    std::cout << "=============================\n";
                }
                removeExpiredEffects(enemies[i]);
            }
            isCharTurn = !isCharTurn;
        }

        if (c.getCurrentHealth() <= 0) {
            return false;
        }

        if (enemies[i]->getCurrentHealth() <= 0) {
            std::cout << "BERHASIL MENGALAHKAN " << enemies[i]->getName() << std::endl;
            prize.addExp(enemies[i]->getExpReward());
            for (auto* loot : enemies[i]->dropLoot()) {
                if (loot != nullptr) {
                    prize.addItem(loot, 1);
                }
            }
        }
    }
    prize.addExp(rewardExp);
    prize.addGold(rewardGold);
    c.reset();
    return true;
}

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
        std::cout << "Enemy " << i + 1 << ": " << std::endl;
        std::cout << enemies[i]->getName() << std::endl;
        std::cout << "Level: " << enemies[i]->getLevel() << std::endl;
        std::cout << "Health: " << enemies[i]->getCurrentHealth() << "/"
                  << enemies[i]->getMaxHealth() << std::endl;
        std::cout << "Health Regen: " << enemies[i]->getHealthRegen()
                  << std::endl;
        std::cout << "Mana: " << enemies[i]->getCurrentMana() << "/"
                  << enemies[i]->getMaxMana() << std::endl;
        std::cout << "Mana Regen: " << enemies[i]->getManaRegen() << std::endl;
        std::cout << "Attack Damage: " << enemies[i]->getAttackDamage()
                  << std::endl;
        std::cout << "Exp Reward: " << enemies[i]->getExpReward() << std::endl;
        std::cout << "Intelligence: "
                  << enemies[i]->getStats().getIntelligence() << std::endl;
        std::cout << "Agility: " << enemies[i]->getStats().getAgility()
                  << std::endl;
        std::cout << "Strength: " << enemies[i]->getStats().getStrength()
                  << std::endl;
        std::cout << "Exp Reward: " << enemies[i]->getExpReward() << std::endl;
        std::cout << "Skills: " << std::endl;
        int ctr = 1;
        for (auto* skill : enemies[i]->getSkills()) {
            std::cout << "    " << ctr << ". " << skill->getName() << std::endl;
            std::cout << "    Name: " << skill->getName() << std::endl;
            std::cout << "    Mana Cost: " << skill->getManaCost() << std::endl;
            std::cout << "    Master Cost: " << skill->getMasterCost()
                      << std::endl;
            std::cout << "    Skill Chance: " << skill->getskillChance()
                      << std::endl;
            std::cout << "    Damage: " << skill->getDamage() << std::endl;
            ctr++;
            int ctr2 = 1;
            for (auto* effect : skill->getEffects()) {
                std::cout << "        " << ctr2 << ". " << effect->getName()
                          << std::endl;
                std::cout << "        Effect: " << effect->getName()
                          << std::endl;
                std::cout << "        Effect Desc: " << effect->getDescription()
                          << std::endl;
                std::cout << "        Effect Duration: "
                          << effect->getDuration() << std::endl;
                std::cout << "        Effect RemainingDur: "
                          << effect->getRemainingDuration() << std::endl;
            }
        }
        std::cout << "Active Effects: " << std::endl;
        int ctr3 = 1;
        for (auto* effect : enemies[i]->getActiveEffects()) {
            std::cout << "    " << ctr3 << ". " << effect->getName()
                      << std::endl;
            std::cout << "    Effect: " << effect->getName() << std::endl;
            std::cout << "    Effect Desc: " << effect->getDescription()
                      << std::endl;
            std::cout << "    Effect Duration: " << effect->getDuration()
                      << std::endl;
            std::cout << "    Effect RemainingDur: "
                      << effect->getRemainingDuration() << std::endl;
            ctr3++;
        }
        std::cout << "Loot Drop: BELOM ADA GETTERNYA!" << std::endl;
        std::cout << "============================" << std::endl;
    }
}

int Chamber::inputOption() {
    int opt;
    bool isValid = false;
    while (!isValid) {
        std::cout << "Aksi -> 1. Attack / 2. Use Skill / 3. Use Item / 4. Kabur : ";
        std::cin >> opt;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Masukan tidak valid." << std::endl;
        } else if (opt >= 1 && opt <= 4) {
            isValid = true;
        } else {
            std::cout << "Masukan tidak valid." << std::endl;
        }
    }

    return opt;
}

void Chamber::removeExpiredEffects(Unit* u) {
    std::vector<Effect*> toRemove;
    for (auto* effect : u->getActiveEffects()) {
        std::cout << "Effect: " << effect->getName() << " -> "
                  << effect->getRemainingDuration() << " turn left\n";
        if (effect->getRemainingDuration() <= 0) {
            std::cout << "Effect Deleted: " << effect->getName() << " expired\n";
            toRemove.push_back(effect);
        }
    }

    for (auto* effect : toRemove) {
        u->removeActiveEffect(effect);
    }
}

int Chamber::inputSkillOption(Unit* u) {
    int opt;
    bool isValid = false;
    while (!isValid) {
        int ctr = 1;
        cin >> opt;
        for (auto* skill : u->getSkills()) {
            std::cout << ctr << ". " << skill->getName() << std::endl;
            ctr++;
        }
        std::cout << "Pilih skill: ";

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Masukan tidak valid." << std::endl;
        } else if (opt >= 1 && opt <= u->getSkills().size()) {
            isValid = true;
        } else {
            std::cout << "Masukan tidak valid." << std::endl;
        }
    }

    return opt;
}

string Chamber::inputItemOption(Inventory& inv) {
    string opt;
    inv.displayBackpack();
    std::cout << "Pilih item: ";
    std::cin >> opt;
    return opt;
}

void Chamber::displayPlayerStatus(Character &c) {
    std::cout << c.getName() << "'s Status\n";
    std::cout << "Health: " << c.getCurrentHealth() << "/" << c.getMaxHealth() << " | +" << c.getHealthRegen() << "/turn\n";
    std::cout << "Mana: " << c.getCurrentMana() << "/" << c.getMaxMana() << " | +" << c.getManaRegen() << "/turn\n";
    std::cout << "Active Effects: \n";
    for (auto* effect : c.getActiveEffects()) {
        std::cout << "    " << effect->getName() << " -> " << effect->getRemainingDuration() << "turn left\n";
    }
}

void Chamber::displayEnemyStatus(Mobs *enemy) {
    std::cout << enemy->getName() << "'s Status\n";
    std::cout << "Health: " << enemy->getCurrentHealth() << "/" << enemy->getMaxHealth() << " | +" << enemy->getHealthRegen() << "/turn\n";
    std::cout << "Mana: " << enemy->getCurrentMana() << "/" << enemy->getMaxMana() << " | +" << enemy->getManaRegen() << "/turn\n";
    std::cout << "Active Effects: \n";
    for (auto* effect : enemy->getActiveEffects()) {
        std::cout << "    " << effect->getName() << " -> " << effect->getRemainingDuration() << "turn left\n";
    }
}