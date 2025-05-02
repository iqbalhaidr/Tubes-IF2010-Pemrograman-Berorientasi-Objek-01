#include "Player.hpp"

Player::Player(std::string dir, std::string charType, Items& itemMap, Characters& allChar){
    this->inv = &Inventory::loadInventory(dir, itemMap);
    this->playerChar = allChar.getCharacterbyName(charType);
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

    inv->addItem({item, 1});
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


