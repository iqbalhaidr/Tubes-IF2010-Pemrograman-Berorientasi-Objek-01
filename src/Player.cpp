#include "../include/Player.hpp"
#include "../include/shop.hpp"
#include "../include/character.hpp"
#include "../include/unit.hpp"
#include "../include/inventory.hpp"
#include "../include/items.hpp"
#include "../include/item.hpp"
#include "../include/effect.hpp"

void runShopMenu(Player& p1, Shop& shop) {
    std::string command;

    while (true) {
        std::cout << "Current Currency ";
        p1.showCurrency();
        std::cout << "\n";
        std::cout << "\n=== Menu ===\n";
        std::cout << "1. Display Shop\n";
        std::cout << "2. Display Backpack\n";
        std::cout << "3. Display Equipment\n";
        std::cout << "4. Buy Item\n";
        std::cout << "5. Sell Item\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter command number: ";
        std::cin >> command;

        try {
            if (command == "1") {
                shop.displayShop();
            }
            else if (command == "2") {
                p1.showInventory(true);
            }
            else if (command == "3") {
                p1.showInventory(false);
            }
            else if (command == "4") {
                std::string itemName;
                int qty;
                std::cout << "Enter item name to buy: ";
                std::cin >> itemName;
                std::cout << "Enter quantity: ";
                std::cin >> qty;
                p1.buyFromShop(shop, itemName, qty);
            }
            else if (command == "5") {
                std::string itemId;
                int qty;
                std::cout << "Enter item id to sell: ";
                std::cin >> itemId;
                std::cout << "Enter quantity: ";
                std::cin >> qty;
                p1.sellToShop(shop, itemId, qty);
            }
            else if (command == "6") {
                std::cout << "Exiting menu.\n";
                break;
            }
            else {
                std::cout << "Invalid command.\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "❌ Error: " << e.what() << std::endl;
        }
        catch (...) {
            std::cerr << "❌ Unknown error occurred" << std::endl;
        }
    }
}


Player::Player(const std::string& dir, const std::string& charType, Items& itemMap, Characters& allChar){
    this->inv = new Inventory(Inventory::loadInventory(dir, itemMap));
    this->playerChar = new Fighter("Kelra",  26, 17, 13, 1, 0,99999999, 0);
    std::cout<<"test";
}

Player::~Player(){
    delete inv;
    delete playerChar;
}

void Player::showCurrency(){
    cout<<playerChar->getGold();
}

void Player::showInventory(bool isBackpack){
    if(isBackpack){
        inv->displayBackpack();
    }
    else{
        inv->displayEquipment();
    }
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

void Player::buyFromShop(Shop& shop, const std::string& itemName, int quantity){
    if (quantity <= 0) 
        throw InvalidValue("Quantity must be positive");
    auto itemPriceAndStock = shop.buyItem(itemName, quantity); //{priceTotal, stock}

    // VALIDASI CURRENCY
    Item* item = itemPriceAndStock.first;  // ambil Item*
    int price  = itemPriceAndStock.second;  // ambil harga (int)
    cout<<item->getName()<<"INI NAMA DALAM BUY FROM SHOP HASIL RETURN BUY ITEM\n";

    if(item==nullptr){
        throw StockError("INI NULL PTR");
    }
    if(playerChar==nullptr){
        throw StockError("INI NULL PTR");
    }
    if(playerChar->getGold()< price){
        cout<<playerChar->getGold()<<"\n";
        cout<<price<<"\n";
        throw GoldNotEnough();
    }
    cout<<"BERHASIL MASUK2\n";
    std::pair<Item*, int> addedItem = std::make_pair(item,quantity);
    
    inv->addItem(addedItem);
    playerChar->setGold(playerChar->getGold()-price);
    cout<<"Berhasil set gold dan add item\n";
    //update shop stock

    auto currStock =shop.getCurrentStock(itemName);
    shop.setStock(itemName,currStock-quantity);
    cout<<"Berhasil update shop stock\n";

    // Delete Unused Pointer to Avoid Memorly Leak
    cout<<"BERHASIL Keluar\n";
}


void Player::sellToShop(Shop& shop, const std::string& itemName, int quantity){
    auto itemInventory = inv->getItemBackpackByName(itemName);
    cout<<"BERHASIL MASUK KE SSELL SHOP\n";

    if(itemInventory.first==nullptr){
        cout<<"EROR ini\n";
        throw ItemNotFound("Item Tidak ada dalam backpack");
    }
    cout<<"Cek1.5\n";
    if(inv->getItemQtyInInvent(itemName) < quantity){
        cout<<"EROR2 ini\n";
        throw StockError("Jumlah item yang ingin dijual lebih besar dari banyak item di inventory");
    }

    cout<<"Cek2\n";
    auto itemShop = shop.sellItem(itemName, quantity); // Dapat throw eror
    auto price = itemShop.second;

    //update shop stock
    cout<<"Cek3\n";
    auto currStock =shop.getCurrentStock(itemName);
    shop.setStock(itemName,currStock+quantity);
    

    cout<<"Cek4\n";
    inv->reduceItem(itemInventory.first, quantity);
    playerChar->setGold(playerChar->getGold()+price);

    // Delete Unused Pointer to Avoid Memorly Leak
    cout<<"Cek5\n";
    delete itemShop.first;
}



int main() {
    cout << "HAI" << endl;
    Characters allChar("../data/");
    cout << "HAI charac" << endl;
    
    Items itemMap = Items::createFromDirectory("../data/");
    cout << "HAI itemMap" << endl;

    Shop shop("../data/");
    cout << "HAI berhasil" << endl;
    
    Player p1("../data/", "Fighter", itemMap, allChar);
    cout << "HAI player" << endl;

    runShopMenu(p1, shop);
    return 0;
}

//command to start test run
// g++ -o player Player.cpp items.cpp item.cpp effect.cpp EffectDamage.cpp EffectDefensive.cpp EffectHealthRegen.cpp EffectManaRegen.cpp EffectPoison.cpp EffectTurnBased.cpp  EffectHealth.cpp EffectTurn.cpp Weapon.cpp Pendant.cpp Armor.cpp Potion.cpp unit.cpp stats.cpp Skill.cpp Randomizer.cpp mobloot.cpp Dungeon.cpp Chamber.cpp Reward.cpp fighter.cpp character.cpp darkKnight.cpp demonLord.cpp goblin.cpp lich.cpp mobs.cpp necromancer.cpp ogre.cpp orc.cpp skeleton.cpp slime.cpp bossMobs.cpp basicMobs.cpp inventory.cpp EffectManaReduc.cpp characters.cpp shop.cpp skillNode.cpp skilltree.cpp mage.cpp berserker.cpp assassin.cpp




