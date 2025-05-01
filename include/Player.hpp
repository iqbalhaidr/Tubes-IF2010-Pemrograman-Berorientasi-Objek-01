#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "character.hpp"
#include "fighter.hpp"
#include "mage.hpp"
#include "assassin.hpp"
#include "necromancer.hpp"
#include "berserker.hpp"
#include "inventory.hpp"


class Player
{
private:
    Inventory inv;
    Character* playerChar;
public:
    Player(/* args */);
    ~Player();

    
};




#endif