#include "../include/Player.hpp"
#include "../include/shop.hpp"
#include "../include/character.hpp"
#include "../include/unit.hpp"
#include "../include/inventory.hpp"
#include "../include/items.hpp"
#include "../include/item.hpp"
#include "../include/effect.hpp"

Player::Player(const std::string& dir, const std::string& charType, Items& itemMap){
    Inventory inv =Inventory::loadInventory(dir, itemMap);
    this->inv = &inv;
    this->playerChar = new Fighter("Fighter");
}

Player::~Player(){
    delete inv;
    delete playerChar;
}

void Player::equipItem(const std::string& slot, Item* item){
    for (Effect* effect : item->getEffects()) {
        playerChar->addActiveEffect(effect);
    }

    if (slot == "WEAPON") {
        playerChar->setAttackDamage(playerChar->getAttackDamage() + item->getFinalStat());
    }


    inv->setEquipped(slot, item);
    inv->reduceItem(item, 1);


}

void Player::onUnEquip(const std::string& slot) {
    Item* item = inv->unequipItem(slot);
    if (item == nullptr){
        throw InventoryEror("Maaf anda mengakses slot equipment yang kosong"); // bisa throw eror
    } 

    for (Effect* effect : item->getEffects()) {
        playerChar->removeActiveEffect(effect);
    }

    if (slot == "WEAPON") {
        playerChar->setAttackDamage(playerChar->getAttackDamage() - item->getFinalStat());
    }

    std::pair<Item*, int> addedItem = {item,1};
    inv->addItem(addedItem);
}


void Player:: useItem(const std::string& itemId){
    auto [item, count] = inv->getItemById(itemId);
    if (item == nullptr) return;

    if (!item->isConsumable()) {
        std::string type = item->getItemType();

        if (type == "Weapon") {
            onUnEquip("WEAPON");
            equipItem("WEAPON", item);
        }
        else if (type == "Pendant") {
            onUnEquip("PENDANT");
            equipItem("PENDANT", item);
        }
        else if (type == "Armor") {
            std::vector<std::string> armorSlots = {"ARMOR_BODY", "ARMOR_FOOT", "ARMOR_HEAD"};
            for (const auto& slot : armorSlots) {
                if (inv->getEquippedItem(slot) == nullptr) {
                    equipItem(slot, item);
                    return;
                }
            }

            std::string minSlot = "";
            int minStat = INT_MAX;
            for (const auto& slot : armorSlots) {
                Item* equipped = inv->getEquippedItem(slot);
                if (equipped && equipped->getFinalStat() < minStat) {
                    minStat = equipped->getFinalStat();
                    minSlot = slot;
                }
            }

            if (!minSlot.empty()) {
                onUnEquip(minSlot);
                equipItem(minSlot, item);
            }
        }
    }
    else {
        for (Effect* effect : item->getEffects()) {
            playerChar->addActiveEffect(effect);
        }
    }
}

void Player::buyFromShop(Shop& shop, const std::string& itemId, int quantity){
    if (quantity <= 0) 
        throw InvalidValue("Quantity must be positive");
    auto itemPriceAndStock = shop.buyItem(itemId, quantity); //{priceTotal, stock}

    // VALIDASI CURRENCY
    Item* item = std::get<0>(itemPriceAndStock);  // ambil Item*
    int price  = std::get<1>(itemPriceAndStock);  // ambil harga (int)

    if(playerChar->getGold()< price){
        throw GoldNotEnough();
    }

    std::pair<Item*, int> addedItem = {item,quantity};
    inv->addItem(addedItem);
    playerChar->setGold(playerChar->getGold()-price);

    //update shop stock
    auto currStock =shop.getCurrentStock(itemId);
    shop.setStock(itemId,currStock-quantity);

    // Delete Unused Pointer to Avoid Memorly Leak
    delete item;
}


int Player::sellToShop(Shop& shop, const std::string& itemId, int quantity){
    auto itemInventory = inv->getItemById(itemId);

    if(quantity > itemInventory.second){
        throw StockError("Jumlah item yang ingin dijual lebih besar dari banyak item di inventory");
    }

    auto itemShop = shop.sellItem(itemId, quantity); // Dapat throw eror
    auto price = itemShop.second;

    inv->reduceItem(itemInventory.first, quantity);
    playerChar->setGold(playerChar->getGold()+price);

    //update shop stock
    auto currStock =shop.getCurrentStock(itemId);
    shop.setStock(itemId,currStock+quantity);

    // Delete Unused Pointer to Avoid Memorly Leak
    delete itemShop.first;
}



int main() {
    try {
        cout << "HAI" << endl;
        // Characters allChar("../data/");
        // cout << "HAI charac" << endl;
        
        Items itemMap = Items::createFromDirectory("../data/");
        cout << "HAI itemMap" << endl;

        Shop shop("../data/");
        cout << "HAI berhasil" << endl;
        
        // Player p1("../data/", "Fighter", itemMap);
        // cout << "HAI player" << endl;
        
    
    }
    catch (const exception& e) {  // Menangkap semua exception standar
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    catch (...) {  // Menangkap semua exception lainnya
        cerr << "Unknown error occurred" << endl;
        return 1;
    }
    
    return 0;
}



