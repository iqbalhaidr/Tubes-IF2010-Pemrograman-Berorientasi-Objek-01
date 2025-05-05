#include "../include/Chamber.hpp"

#include <iostream>

// DONE
Chamber::Chamber(bool isLast, int minMobLevel, int maxMobLevel, Mobloot& mobLoots)
    : isLastChamber(isLast),
      minMobLevel(minMobLevel),
      maxMobLevel(maxMobLevel),
      mobLoots(&mobLoots) {
    rewardExp = generateRewardExp();
    rewardGold = generateRewardGold();
    autoMenang = false;
    cheatEnemyStun = false;
    cheatDamage = false;
    cheatGod = false;
    generateEnemies();
}

// DONE
Chamber::Chamber(const Chamber& c) {
    this->rewardExp = c.rewardExp;
    this->rewardGold = c.rewardGold;
    this->enemyCount = c.enemyCount;
    this->isLastChamber = c.isLastChamber;
    this->minMobLevel = c.minMobLevel;
    this->maxMobLevel = c.maxMobLevel;
    this->mobLoots = c.mobLoots;
    this->autoMenang = c.autoMenang;

    this->enemies = c.enemies;
}

// DONE
Chamber::~Chamber() {
    for (int i = 0; i < enemyCount; i++) {
        delete enemies[i];
    }
    enemies.clear();
}

// DONE
Chamber& Chamber::operator=(const Chamber& c) {
    this->rewardExp = c.rewardExp;
    this->rewardGold = c.rewardGold;
    this->enemyCount = c.enemyCount;
    this->isLastChamber = c.isLastChamber;
    this->minMobLevel = c.minMobLevel;
    this->maxMobLevel = c.maxMobLevel;
    this->mobLoots = c.mobLoots;
    this->autoMenang = c.autoMenang;
    this->enemies = c.enemies;

    return *this;
}

// DONE
int Chamber::getRewardExp() const { return rewardExp; }
int Chamber::getRewardGold() const { return rewardGold; }
int Chamber::getEnemyCount() const { return enemyCount; }
int Chamber::isLast() const { return isLastChamber; }
int Chamber::getMinMobLevel() const { return minMobLevel; }
int Chamber::getMaxMobLevel() const { return maxMobLevel; }
std::vector<Mobs*> Chamber::getEnemies() const { return enemies; }

// DONE
int Chamber::generateRewardGold() {
    int a = 2;
    int b = 3;
    int c = 1;
    return a * minMobLevel + b * maxMobLevel + c * (maxMobLevel - minMobLevel);
}

// DONE
int Chamber::generateRewardExp() {
    int a = 4;
    int b = 6;
    int c = 2;
    return a * minMobLevel + b * maxMobLevel + c * (maxMobLevel - minMobLevel);
}

// DONE
int Chamber::generateEnemyCount() {
    if (isLastChamber) {
        return Randomizer::random(MIN_ENEMIES_LAST_CHAMBER, MAX_ENEMIES_LAST_CHAMBER);
    } else {
        return Randomizer::random(MIN_ENEMIES_CHAMBER, MAX_ENEMIES_CHAMBER);
    }
}

// DONE
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

// DONE
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
    bool isBossSpawnedInBasicChamber = false;
    enemyCount = generateEnemyCount();
    for (int i = 0; i < enemyCount; i++) {
        if (isLastChamber) {
            int level = Randomizer::random(minMobLevel, maxMobLevel);
            // std::cout << "Mobs level: " << level << std::endl;
            enemies.push_back(generateBossMobs(level));
        } else {
            if (!isBossSpawnedInBasicChamber) {
                if (Randomizer::chance(CHANCE_BOSS_NOT_ON_LAST_CHAMBER)) {
                    int level = Randomizer::random(minMobLevel, maxMobLevel);
                    enemies.push_back(generateBossMobs(level));
                    // std::cout << "Mobs level: " << level << std::endl;
                    isBossSpawnedInBasicChamber = true;
                } else {
                    int level = Randomizer::random(minMobLevel, maxMobLevel);
                    enemies.push_back(generateBasicMobs(level));
                    // std::cout << "Mobs level: " << level << std::endl;
                }
            } else {
                int level = Randomizer::random(minMobLevel, maxMobLevel);
                enemies.push_back(generateBasicMobs(level));
                // std::cout << "Mobs level: " << level << std::endl;
            }
        }
    }
}

bool Chamber::battle(Character& c, Inventory& inv, Reward& prize, Items& items) {
    for (int i = 0; i < enemyCount; i++) {
        bool isCharTurn = true;
        int turnCtr = 0;
        while (enemies[i]->getCurrentHealth() > 0 && c.getCurrentHealth() > 0 && !autoMenang) {
            if (isCharTurn) {
                if (c.getTurnEffectStatus("Stun")) {  // Cek apakah ada activeEffect stun
                    std::cout << "\e[1;1H\e[2J"; //Clear console
                    displayStatus(c, enemies[i]);
                    std::cout << c.getName() << " Terkena Stun! Tidak dapat beraksi pada turn ini.\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                    std::cout << "\e[1;1H\e[2J"; //Clear console

                    std::cout << "\e[1;1H\e[2J"; //Clear console
                    c.applyActiveEffect();
                    removeExpiredEffects(&c);
                    displayStatus(c, enemies[i]);
                    std::cout << c.getName() << " post-apply active effect\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                    std::cout << "\e[1;1H\e[2J"; //Clear console

                    turnCtr++;
                    isCharTurn = !isCharTurn;
                    continue;
                }

                // std::cout << "\n==========================\n";
                // std::cout << "SETELAH APPLY EFFECT\n";
                // std::cout << "\n==========================\n";
                std::cout << "\e[1;1H\e[2J"; //Clear console
                c.applyActiveEffect();
                removeExpiredEffects(&c);
                displayStatus(c, enemies[i]);
                std::cout << c.getName() << " post-apply active effect\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                std::cout << "\e[1;1H\e[2J"; //Clear console

                // Regen health and mana (hanya dipanggil jika tidak ada efek stun)
                c.heal(c.getHealthRegen());
                c.restoreMana(c.getManaRegen());
                displayStatus(c, enemies[i]);
                std::cout << c.getName() << "'s wounds begin to close as arcane energy returns to his veins.\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                std::cout << "\e[1;1H\e[2J"; //Clear console

                std::cout << "\e[1;1H\e[2J"; //Clear console
                std::cout << "Enemy: " << i << "/" << enemyCount << " | Turn: " << turnCtr << std::endl;
                std::cout << "\n";
                displayStatus(c, enemies[i]);
                // std::cout << "\n";
                // std::cout << "==============================================\n\n";

                int opt = inputOption();
                if (opt == 1) {
                    c.attack(*enemies[i], inv);

                    std::cout << "\e[1;1H\e[2J"; //Clear console
                    std::cout << c.getName() << " launches an attack to " << enemies[i]->getName() << "!\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));

                    displayStatus(c, enemies[i]);

                    // std::cout << "\n=============================\n";
                    // std::cout << "Character Attack! Chamber.cpp\n";
                    // std::cout << "Enemy Status Post-Attack: \n";
                    // displayEnemyStatus(enemies[i]);
                    // std::cout << "=============================\n";
                } else if (opt == 2) {
                    // std::cout << "\n=============================\n";
                    if (c.getSkills().empty()) {
                        std::cout << "\e[1;1H\e[2J"; //Clear console
                        std::cout << "No skills available to use right now." << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                        // std::cout << "=============================\n";
                        continue;
                    }

                    std::cout << "\e[1;1H\e[2J"; //Clear console
                    int skillOpt = inputSkillOption(&c);
                    c.useSkill(c.getSkills()[skillOpt - 1], *enemies[i], inv);

                    std::cout << "\e[1;1H\e[2J"; //Clear console
                    std::cout << c.getName() << " activates " << c.getSkills()[skillOpt - 1]->getName() << "!\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                    displayStatus(c, enemies[i]);
                    // std::cout << "Enemy Status Post-Useskill from char: \n";
                    // displayEnemyStatus(enemies[i]);
                    // std::cout << "=============================\n";
                    
                } else if (opt == 3) {
                    useItemOption(c, inv, items, *enemies[i]);
                } else if (opt == 4) {  // KABUR
                    return false;
                } else if (opt == 5) {  // CHEAT AUTOWIN
                    cheatMode(c, prize);
                }
                // removeExpiredEffects(&c);

                // std::cout << "==============================\n";
                // std::cout << "Remove expired effects called\n";
                // displayPlayerStatus(c);
                // std::cout << "==============================\n";

                turnCtr++;
            } else {
                if (enemies[i]->isBoss()) {
                    int percentHealth = int(enemies[i]->getCurrentHealth() * 100 / enemies[i]->getMaxHealth());
                    BossMobs* b = dynamic_cast<BossMobs*>(enemies[i]);
                    if (percentHealth <= 20 && !b->isRageUsed()) {
                        b->rage();
                        std::cout << "\e[1;1H\e[2J"; //Clear console
                        std::cout << "Tersudut dan terluka, " << b->getName() <<  " masuk ke dalam keadaan mengamuk. Aura kekuatannya melonjak tajam!\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                        std::cout << "\e[1;1H\e[2J"; //Clear console
                    }
                }
                
                // std::cout << "Enemy Turn! Chamber.cpp\n";
                // std::cout << "Enemy level: " << enemies[i]->getLevel() << std::endl;
                if (enemies[i]->getTurnEffectStatus("Stun") || cheatEnemyStun) {
                    // std::cout << "\n==========================\n";
                    // std::cout << "Enemy Terkena Stun! Chamber.cpp\n";
                    // std::cout << "Enemy post-apply active effect\n";
                    std::cout << "\e[1;1H\e[2J"; //Clear console
                    displayStatus(c, enemies[i]);
                    std::cout << enemies[i]->getName() << " Terkena Stun! Tidak dapat beraksi pada turn ini.\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                    std::cout << "\e[1;1H\e[2J"; //Clear console

                    std::cout << "\e[1;1H\e[2J"; //Clear console
                    enemies[i]->applyActiveEffect();
                    removeExpiredEffects(enemies[i]);
                    displayStatus(c, enemies[i]);
                    std::cout << enemies[i]->getName() << " post-apply active effect\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                    std::cout << "\e[1;1H\e[2J"; //Clear console
                    // std::cout << "==========================\n";

                    // turnCtr++;
                    isCharTurn = !isCharTurn;
                    continue;
                }
                // std::cout << "\n==========================\n";
                // std::cout << "Enemy post-apply active effect\n";
                std::cout << "\e[1;1H\e[2J"; //Clear console
                enemies[i]->applyActiveEffect();
                removeExpiredEffects(enemies[i]);
                displayStatus(c, enemies[i]);
                std::cout << enemies[i]->getName() << " post-apply active effect\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                std::cout << "\e[1;1H\e[2J"; //Clear console
                // std::cout << "==========================\n";

                // Regen health and mana (hanya dipanggil jika tidak ada efek
                // stun)
                enemies[i]->heal(enemies[i]->getHealthRegen());
                enemies[i]->restoreMana(enemies[i]->getManaRegen());
                displayStatus(c, enemies[i]);
                std::cout << enemies[i]->getName() << "'s wounds begin to close as arcane energy returns to his veins.\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                std::cout << "\e[1;1H\e[2J"; //Clear console
                // std::cout << "Enemy regen called\n";

                std::cout << "\e[1;1H\e[2J"; //Clear console
                std::cout << "Enemy: " << i << "/" << enemyCount << " | Turn: " << turnCtr << std::endl;
                std::cout << "\n";
                displayStatus(c, enemies[i]);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));

                int opt = Randomizer::random(1, 3);
                // int opt = 2;
                if (opt == 1 || opt == 3) {
                    
                    std::cout << "\e[1;1H\e[2J"; //Clear console
                    std::cout << enemies[i]->getName() << " launches an attack to " << c.getName() << "!\n";
                    if (!cheatGod) {
                        enemies[i]->attack(c, inv);
                    } else {
                        std::cout << "Kebal dari serangan (godMode)\n";
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                    displayStatus(c, enemies[i]);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));

                    // std::cout << "\n=============================\n";
                    // std::cout << "Enemy Attack! Chamber.cpp\n";
                    // std::cout << "Character Status Post-Attack: \n";
                    // displayPlayerStatus(c);
                    // std::cout << "=============================\n";

                } else if (opt == 2) {
                    if (c.getSkills().empty()) {
                        // std::cout << "No skills available." << std::endl;
                        continue;
                    }
                    int skillOpt = Randomizer::random(1, enemies[i]->getSkills().size() - 1);
                    // std::cout << "Enemy pasti skill 1\n";
                    // int skillOpt = 1;
                    // std::cout << "Skill enemy tidak mungkin heal untuk keperluan debugging\n";
                    // enemies[i]->useSkill(enemies[i]->getSkills()[skillOpt], c, inv);
                    
                    std::cout << "\e[1;1H\e[2J"; //Clear console
                    std::cout << enemies[i]->getName() << " activates " << enemies[i]->getSkills()[skillOpt]->getName() << "!\n";
                    if (!cheatGod) {
                        enemies[i]->useSkill(enemies[i]->getSkills()[skillOpt], c, inv);
                    } else {
                        std::cout << "Kebal dari serangan (godMode)\n";
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                    displayStatus(c, enemies[i]);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                    // std::cout << "\n=============================\n";
                    // std::cout << "Enemy uses: " << enemies[i]->getSkills()[skillOpt]->getName() << std::endl;
                    // std::cout << "Character Status Post-Useskill from enemy: \n";
                    // displayPlayerStatus(c);
                    // std::cout << "=============================\n";
                }
                // removeExpiredEffects(enemies[i]);
            }
            isCharTurn = !isCharTurn;
        }

        if (c.getCurrentHealth() <= 0) {
            return false;
        }

        if (enemies[i]->getCurrentHealth() <= 0 || autoMenang) {
            std::cout << "\e[1;1H\e[2J"; //Clear console
            std::cout << "As the " << enemies[i]->getName() << " collapses, its body dissolves—leaving behind a trove of glimmering loot.\n";
            std::cout << "Exp reward: " << enemies[i]->getExpReward() << std::endl;
            std::cout << "Item drop: \n";

            int ctr = 1;
            prize.addExp(enemies[i]->getExpReward());
            for (auto* loot : enemies[i]->dropLoot()) {
                if (loot != nullptr) {
                    std::cout << "    " << ctr << ". " << loot->getName() << std::endl;
                    prize.addItem(loot, 1);
                    ctr++;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
            std::cout << "\e[1;1H\e[2J"; //Clear console
        }
    }
    prize.addExp(rewardExp);
    prize.addGold(rewardGold);

    std::cout << "\e[1;1H\e[2J"; //Clear console
    std::cout << "With the last foe vanquished, " << c.getName() << " surveys the silent chamber. \nAs the dust settles, a hidden vault creaks open—revealing his rightful reward.\n";
    std::cout << "Exp reward: " << rewardExp << std::endl;
    std::cout << "Gold reward: " << rewardGold << std::endl;
    std::cout << "\nPotential Reward: \n";
    prize.displayInfo();

    std::cout << "\n[PRESS ENTER TO CONTINUE]";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    std::cout << "\e[1;1H\e[2J"; //Clear console

    if (cheatDamage) {
        c.setAttackDamage(c.getAttackDamage() - BIG_DAMAGE);
    }

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
        std::cout << "Aksi -> 1. Attack / 2. Use Skill / 3. Use Item / 4. Kabur / 5. Cheat: ";
        std::cin >> opt;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Masukan tidak valid." << std::endl;
        } else if (opt >= 1 && opt <= 5) {
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
        if (effect->getRemainingDuration() < 0) {
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
        for (auto* skill : u->getSkills()) {
            std::cout << ctr << ". " << skill->getName() << std::endl;
            ctr++;
        }
        std::cout << "Pilih skill: ";
        cin >> opt;

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

// string Chamber::inputItemOption(Inventory& inv) {
//     string opt;
//     inv.displayBackpack();
//     std::cout << "Pilih item: ";
//     std::cin >> opt;
//     return opt;
// }

void Chamber::useItemOption(Character& c, Inventory& inv, Items& itemsMap, Unit& t) {
    bool alreadyUseItem = false;
    while (true) {
        std::cout << "\e[1;1H\e[2J"; //Clear console
        std::cout << "Selamat datang di menu penggunaan item!\n";
        std::cout << "1. Gunakan item\n";
        std::cout << "2. Unequip item\n";
        std::cout << "3. Keluar\n";

        int opt;
        bool isValid = false;
        while (!isValid) {
            std::cout << "Pilih opsi: ";
            std::cin >> opt;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n');
                std::cout << "Masukan tidak valid." << std::endl;
            } else if (opt >= 1 && opt <= 3) {
                isValid = true;
            } else {
                std::cout << "Masukan tidak valid." << std::endl;
            }
        }

        if (opt == 1) {
            if (alreadyUseItem) {
                std::cout << "\e[1;1H\e[2J"; //Clear console
                std::cout << "Dalam 1 Turn hanya bisa menggunakan 1 item!\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
            } else {
                alreadyUseItem = useItemMenu(c, inv, itemsMap, t);
            }
        } else if (opt == 2) {
            unequipMenu(c, t, inv);
        } else if (opt == 3) {
            return;
        }
    }
}

bool Chamber::useItemMenu(Character& c, Inventory& inv, Items& itemsMap, Unit& t) {
    std::cout << "\e[1;1H\e[2J"; //Clear console
    std::cout << "Items di Backpack: \n";
    inv.displayBackpack();

    std::cout << "Pilih item yang ingin digunakan (KELUAR): ";
    std::string opt;
    std::cin >> opt;

    if (opt == "KELUAR") {
        return false;
    }
    inv.useItem(opt, c, itemsMap, t);
    std::cout << "\e[1;1H\e[2J"; //Clear console
    std::cout << c.getName() << " uses " << opt << "!\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
    return true;
}

void Chamber::unequipMenu(Character& c, Unit& t, Inventory& inv) {
    while (true) {
        // std::cout << "\n==========================\n";
        std::cout << "\e[1;1H\e[2J"; //Clear console
        std::cout << "Equipped Items: \n";
        inv.displayEquipment();

        bool isInputTrue = false;
        std::string opt;
        while (!isInputTrue) {
            std::cout << "Pilih item yang ingin di-un-equip (WEAPON/ARMOR_HEAD/ARMOR_BODY/ARMOR_FOOT/PENDANT/KELUAR): ";
            std::cin >> opt;

            if (opt == "WEAPON" || opt == "ARMOR_HEAD" || opt == "ARMOR_BODY" ||
                opt == "ARMOR_FOOT" || opt == "PENDANT" || opt == "KELUAR") {
                isInputTrue = true;
            } else {
                std::cout << "Input tidak valid." << std::endl;
            }
        }

        if (opt == "WEAPON") {
            inv.unequipItem(c, "WEAPON", t);
            std::cout << "\e[1;1H\e[2J"; //Clear console
            std::cout << c.getName() << " unequips the weapon.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
        } else if (opt == "ARMOR_HEAD") {
            inv.unequipItem(c, "ARMOR_HEAD", t);
            std::cout << "\e[1;1H\e[2J"; //Clear console
            std::cout << c.getName() << " unequips the armor head.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
            // std::cout << "Berhasil meng-un-equip armor head" << std::endl;
        } else if (opt == "ARMOR_BODY") {
            inv.unequipItem(c, "ARMOR_BODY", t);
            std::cout << "\e[1;1H\e[2J"; //Clear console
            std::cout << c.getName() << " unequips the armor body.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
            // std::cout << "Berhasil meng-un-equip armor body" << std::endl;
        } else if (opt == "ARMOR_FOOT") {
            inv.unequipItem(c, "ARMOR_FOOT", t);
            std::cout << "\e[1;1H\e[2J"; //Clear console
            std::cout << c.getName() << " unequips the armor foot.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
            // std::cout << "Berhasil meng-un-equip armor foot" << std::endl;
        } else if (opt == "PENDANT") {
            inv.unequipItem(c, "PENDANT", t);
            std::cout << "\e[1;1H\e[2J"; //Clear console
            std::cout << c.getName() << " unequips the pendant.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
            // std::cout << "Berhasil meng-un-equip pendant" << std::endl;
        } else if (opt == "KELUAR") {
            return;
        }
        // std::cout << "==========================\n";
    }
}

void Chamber::displayPlayerStatus(Character& c) {
    std::cout << c.getName() << "'s Status\n";
    std::cout << "Health: " << c.getCurrentHealth() << "/" << c.getMaxHealth() << " | +" << c.getHealthRegen() << "/turn\n";
    std::cout << "Mana: " << c.getCurrentMana() << "/" << c.getMaxMana() << " | +" << c.getManaRegen() << "/turn\n";
    std::cout << "Active Effects: \n";
    for (auto* effect : c.getActiveEffects()) {
        std::cout << "    " << effect->getName() << " -> " << effect->getRemainingDuration() << "turn left\n";
    }
}

void Chamber::displayEnemyStatus(Mobs* enemy) {
    std::cout << enemy->getName() << "'s Status (" << enemy->getLevel() << ")\n";
    std::cout << "Health: " << enemy->getCurrentHealth() << "/" << enemy->getMaxHealth() << " | +" << enemy->getHealthRegen() << "/turn\n";
    std::cout << "Mana: " << enemy->getCurrentMana() << "/" << enemy->getMaxMana() << " | +" << enemy->getManaRegen() << "/turn\n";
    std::cout << "Active Effects: \n";
    for (auto* effect : enemy->getActiveEffects()) {
        std::cout << "    " << effect->getName() << " -> " << effect->getRemainingDuration() << " turn left\n";
    }
}

void Chamber::displayStatus(Character& c, Mobs *enemy) {
    std::cout << "\e[1;1H\e[2J";  // Clear console
    displayPlayerStatus(c);
    std::cout << "\n";
    displayEnemyStatus(enemy);
    std::cout << "\n";
}

void Chamber::cheatMode(Character &c, Reward &prize) {
    std::cout << "\e[1;1H\e[2J"; //Clear console
    std::cout << "DISCLAIMER: HANYA BERLAKU PADA CHAMBER SAAT INI!\n";
    std::cout << "Silahkan pilih wahai cheater:\n";
    std::cout << "1. Langsung menang bos\n";
    std::cout << "2. Musuh ke stun mulu\n";
    std::cout << "3. Damage ga ngotak (+9999)\n";
    std::cout << "4. Level up setinggi langit (+100.000.000 exp)\n";
    std::cout << "5. HP/Mana penuh lagi bos\n";
    std::cout << "6. Mode tuhan (gabisa kena serangan musuh)\n";
    std::cout << "7. Hapus semua efek aktif\n";
    std::cout << "Pilihan: ";

    int opt;
    bool isValids = false;
    while (!isValids) {
        std::cout << "Pilihan: ";
        std::cin >> opt;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Masukan tidak valid." << std::endl;
        } else if (opt >= 1 && opt <= 7) {
            isValids = true;
        } else {
            std::cout << "Masukan tidak valid." << std::endl;
        }
    }

    if (opt == 1) {
        autoMenang = true;
    } else if (opt == 2) {
        cheatEnemyStun = true;
    } else if (opt == 3) {
        c.setAttackDamage(c.getAttackDamage() + BIG_DAMAGE);
        cheatDamage = true;
    } else if (opt == 4) {
        prize.addExp(100000000);
    } else if (opt == 5) {
        c.setCurrentHealth(c.getMaxHealth());
        c.setCurrentMana(c.getMaxMana());
    } else if (opt == 6) {
        cheatGod = true;
    } else if (opt == 7) {
        for (auto* effect : c.getActiveEffects()) {
            c.removeActiveEffect(effect);
        }
    }
}
