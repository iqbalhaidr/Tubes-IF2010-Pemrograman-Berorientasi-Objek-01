#include "../include/Player.hpp"
#include "../include/shop.hpp"
#include "../include/character.hpp"
#include "../include/unit.hpp"
#include "../include/inventory.hpp"
#include "../include/items.hpp"
#include "../include/item.hpp"
#include "../include/effect.hpp"
#include "../include/exception.hpp"

void Player:: goToShop(Shop& shop) {
    std::string command;
    Animation animation;
    animation.animateWalkingToShop(animation.shop());

    while (true) {
        std::cout << "Current Currency ";
        this->showCurrency();
        std::cout << "\n";
        std::cout << "\n=== Menu ===\n";
        std::cout << "1. Display Shop\n";
        std::cout << "2. Display Backpack\n";
        std::cout << "3. Display Equipment\n";
        std::cout << "4. Buy Item\n";
        std::cout << "5. Sell Item\n";
        std::cout << "6. Cheat Gold\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter command number: ";
        std::cin >> command;
        int addableQty = 0;
        std::string addAbleItem ="";
        try {
            if (command == "1") {
                shop.displayShop();
            }
            else if (command == "2") {
                this->showInventory(true);
            }
            else if (command == "3") {
                this->showInventory(false);
            }
            else if (command == "4") {
                std::string addAbleItem;
                int addableQty;
            
                std::cout << "Masukkan nama item untuk dibeli: ";
                std::cin >> addAbleItem;
                if (addAbleItem.empty()) {
                    throw InvalidValue("Nama item tidak boleh kosong.");
                }
            
                std::cout << "Masukkan Jumlah: ";
                std::cin >> addableQty;
                if (std::cin.fail() || addableQty <= 0) {
                    std::cin.clear(); // clear error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                    throw InvalidValue("Tolong masukkan jumlah item yang positif.");

                }
            
                this->buyFromShop(shop, addAbleItem, addableQty);
            }
            else if (command == "5") {
                std::string itemId;
                int qty;
            
                std::cout << "Masukkan nama item untuk dijual:  ";
                std::cin >> itemId;
                if (itemId.empty()) {
                    throw InvalidValue("Nama item tidak boleh kosong.");
                }
            
                std::cout << "Masukkan Jumlah: ";
                std::cin >> qty;
                if (std::cin.fail() || qty <= 0) {
                    std::cin.clear(); // clear error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                    throw InvalidValue("Tolong masukkan jumlah item yang positif.");
                }
            
                this->sellToShop(shop, itemId, qty);
            }
            else if (command == "6") {
                int qty;
                std::cout << "Silahkan masukkan banyak gold:  ";
                std::cin >> qty;
                this->setGold(qty);
            }
            else if (command == "7") {
                break;
            }
            else {
                std::cout << "Invalid command.\n";
            }
        }
        catch (const InventoryFull& e) {
            this->reduceItemInvetory(addAbleItem, addableQty-e.getOverflow());
            std::cerr << "Error: " << e.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        catch (...) {
            std::cerr << "Unknown error occurred" << std::endl;
        }
    }
}


Player::Player(const std::string& dir, const std::string& charName, Items& itemMap, Characters& allChar, int type){
    if(type == 0){ // load
        this->playerChar = allChar.getCharacterbyName(charName);
    }
    else if(type == 1){
        this->playerChar = new Berserker(charName);
    }
    else if (type == 2){
        this->playerChar = new Fighter(charName);
    }
    else if(type == 3){
        this->playerChar = new Mage(charName);
    }
    else if (type == 4){
        this->playerChar = new Necromancer(charName);
    }
    else if(type == 5){
        this->playerChar = new Assassin(charName);
    }
    this->itemMap = &itemMap;
    this->inv = new Inventory(Inventory::loadInventory(dir, itemMap));
    // this->playerChar = new Fighter("Kelra",  26, 17, 13, 1, 0,99999999, 0);
}

Player::Player(const std::string& dir, const std::string& charName, Items& itemMap, Characters& allChar, int type, Inventory* inv){
    if(type == 0){ // load
        this->playerChar = allChar.getCharacterbyName(charName);
    }
    else if(type == 1){
        this->playerChar = new Berserker(charName);
    }
    else if (type == 2){
        this->playerChar = new Fighter(charName);
    }
    else if(type == 3){
        this->playerChar = new Mage(charName);
    }
    else if (type == 4){
        this->playerChar = new Necromancer(charName);
    }
    else if(type == 5){
        this->playerChar = new Assassin(charName);
    }
    this->itemMap = &itemMap;
    this->inv = inv;
    // this->playerChar = new Fighter("Kelra",  26, 17, 13, 1, 0,99999999, 0);
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
        inv->displayBackpackDetails();
    }
    else{
        inv->displayEquipment();
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
        cout<<playerChar->getGold()<<" INI DIA GOLDNYA\n";
        cout<<price<<" INI DIA PRICENYA \n";
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

void Player::playerEquip(const std::string& itemId, const std::string& slot ){
    auto item = inv->getItemById(itemId);
    if(item.first == nullptr){
        cout<<"Maaf kamu mengakses item yang tidak ada di tas\n";
        return;
    }
    if(item.first->isConsumable()){
        cout<<"Maaf kamu tidak bisa equip consumable item\n";
        return;
    }
    if((slot == "ARMOR_HEAD" ||  slot == "ARMOR_BODY" || slot == "ARMOR_FOOT") 
    && item.first->getItemType()=="Armor"){
        inv->handleNonConsumable((item.first), *playerChar, *playerChar);
        
    }
    else if((slot == "WEAPON" ) && item.first->getItemType()=="Weapon"){
        inv->handleNonConsumable((item.first), *playerChar, *playerChar);
        
    }
    else if((slot == "PENDANT" ) && item.first->getItemType()=="Pendant"){
        inv->handleNonConsumable((item.first), *playerChar, *playerChar);
        
    }

    std::cout << playerChar->getName()<<" Berhasi equip item " << item.first->getName();
    
}

void Player::playerUnequip(const std::string& slot){
    Item* item = inv->getEquippedItem(slot);
    if (item == nullptr){
        cout << "Maaf kamu tidak bisa melakukan unequip terhadap slot yang kosong\n";
        return;
    } 
    inv->unequipItem(*playerChar, slot , *playerChar);
    std::cout << playerChar->getName() << " unequips " << slot << ".\n";
}


void Player::sellToShop(Shop& shop, const std::string& itemName, int quantity){
    auto itemInventory = inv->getItemBackpackByName(itemName);

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

void Player::setGold(int setGold){
    if(setGold<0){
        throw InvalidValue("Gold dari character tidak boleh < 0");
    }
    playerChar->setGold(setGold);
}

void Player::reduceItemInvetory(const std::string& addAbleItem, int target){
    Item* item = itemMap->getItembyName(addAbleItem);
    inv->reduceItem(item, target);
}

void Player::goToDungeon(Mobloot& moobLoot, Items& items){
    std::cout<<"Masukkan rank" << std::endl;
    std::string input;
    cin>>input;

    Dungeon dungeon(input, moobLoot, items, *playerChar);
    dungeon.start(*playerChar, *inv, items);
}


// int main() {
//     cout << "HAI" << endl;
//     Characters allChar("../data/");
//     cout << "HAI charac" << endl;
    
//     Items itemMap = Items::createFromDirectory("../data/");
//     cout << "HAI itemMap" << endl;

//     Shop shop("../data/");
//     cout << "HAI berhasil" << endl;
    
//     Player p1("../data/", "Fighter", itemMap, allChar);
//     cout << "HAI player" << endl;

//     runShopMenu(p1, shop);
//     return 0;
// }

//command to start test run
// g++ -o player Player.cpp items.cpp item.cpp effect.cpp EffectDamage.cpp EffectDefensive.cpp EffectHealthRegen.cpp EffectManaRegen.cpp EffectPoison.cpp EffectTurnBased.cpp  EffectHealth.cpp EffectTurn.cpp Weapon.cpp Pendant.cpp Armor.cpp Potion.cpp unit.cpp stats.cpp Skill.cpp Randomizer.cpp mobloot.cpp Dungeon.cpp Chamber.cpp Reward.cpp fighter.cpp character.cpp darkKnight.cpp demonLord.cpp goblin.cpp lich.cpp mobs.cpp necromancer.cpp ogre.cpp orc.cpp skeleton.cpp slime.cpp bossMobs.cpp basicMobs.cpp inventory.cpp EffectManaReduc.cpp characters.cpp shop.cpp skillNode.cpp skilltree.cpp mage.cpp berserker.cpp assassin.cpp




