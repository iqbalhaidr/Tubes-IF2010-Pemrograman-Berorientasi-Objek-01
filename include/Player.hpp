#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "character.hpp"
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
    Inventory inv;
    Character* playerChar;
public:
    Player(/* args */);
    ~Player();

    void goToDungeon(std::string rankDungeon); //mekanisme buat dungeon dan start dungeon
    void goToShop(Shop& shop); //

    void useItemInInventory();
};




#endif