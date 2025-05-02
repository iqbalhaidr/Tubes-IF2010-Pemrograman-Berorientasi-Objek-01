#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "character.hpp"
#include "characters.hpp"
#include "exception.hpp"
#include "items.hpp"
#include "fighter.hpp"
#include "mage.hpp"
#include "assassin.hpp"
#include "necromancer.hpp"
#include "berserker.hpp"
#include "inventory.hpp"
#include "shop.hpp"


class Player
{
private:
    Inventory* inv;
    Character* playerChar;
public:
    Player(std::string dir, std::string charType, Items& itemMap, Characters& allChar);
    ~Player();

    // void goToDungeon(std::string rankDungeon); //mekanisme buat dungeon dan start dungeon
    // void goToShop(Shop& shop); //

    void onUnEquip(const std::string& slot);
    void useItem(const std::string& itemId);
    void equipItem(const std::string& slot, Item* item);
};




#endif