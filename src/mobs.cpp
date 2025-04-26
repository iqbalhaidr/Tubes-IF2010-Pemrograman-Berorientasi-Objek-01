#include "mobs.hpp"

Mobs::Mobs(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots)
 : Unit(name, maxHealth, healthRegen, maxMana, manaRegen, attackDamage, strength, agility, intelligence) {
    this->expReward = expReward; 
    this->LootDrop = mobLoots.getLootforMob(name);
}

Mobs::~Mobs() {}

int Mobs::getExpReward() const {
    return expReward;
}

void Mobs::setExpReward(int expReward) {
    this->expReward = expReward;
}

vector<Item*> Mobs::dropLoot() {
    vector<Item*> droppedItem;
    for (const auto& loot : LootDrop) {
        if (rand() % 100 < loot.second) {
            droppedItem.push_back(loot.first);      
        }
    }

    return droppedItem; 
}

void Mobs::reset() {
    currentHealth = maxHealth;
    currentMana = maxMana;
}