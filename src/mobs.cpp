#include "mobs.hpp"

Mobs::Mobs(string name, int level, int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots)
 : Unit(name, strength, agility, intelligence) {
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

// void Mobs::useSkill(string skill, Unit& target){
    // Unit::useSkill(skill, target); // Memanggil fungsi dari Unit
    // if (rand() % 100 < 50) { // 50% chance to heal
        // heal(healValue); // Heal the mob
    // }
// }

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