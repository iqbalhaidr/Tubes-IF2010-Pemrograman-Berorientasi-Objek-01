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
#include "Dungeon.hpp"
#include "mobloot.hpp"
#include "animation.hpp"


class Player
{
private:
    Items* itemMap;
    Inventory* inv;
    Character* playerChar;
public:
    Player(const std::string& dir, const std::string& charType, Items& itemMap, Characters& allChar, int type, Inventory* inv);
    Player(const std::string& dir, const std::string& charType, Items& itemMap, Characters& allChar, int type);
    ~Player();

    void goToDungeon(Mobloot& moobLoot, Items& itemMap); 
    void goToShop(Shop& shop); 
    void buyFromShop(Shop& shop, const std::string& itemId, int quantity); 
    void sellToShop(Shop& shop, const std::string& itemId, int quantity);
    void showInventory(bool isBackpack);
    void showCurrency();
    void reduceItemInvetory(const std::string& addAbleItem, int target);
    void setGold(int setTo);
    void playerEquip(const std::string& id, const std::string& slot);
    void playerUnequip(const std::string& id);
    Character* getChar(){return playerChar;};
    Inventory* getInv(){return inv;};
};




#endif