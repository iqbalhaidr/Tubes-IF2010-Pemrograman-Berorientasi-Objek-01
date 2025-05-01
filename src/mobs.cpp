#include "../include/mobs.hpp"

Mobs::Mobs(string name, int level, int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots)
 : Unit(name, strength, agility, intelligence, level) {
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
        if ((rand() % 100 + 1)< loot.second) {
            droppedItem.push_back(loot.first);      
        }
    }

    return droppedItem; 
}



void Mobs::reset() {
    currentHealth = maxHealth;
    currentMana = maxMana;
}