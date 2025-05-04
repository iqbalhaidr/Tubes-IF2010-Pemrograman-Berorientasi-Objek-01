#include "../include/mobs.hpp"

Mobs::Mobs(string name, int level, int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots)
 : Unit(name, strength, agility, intelligence, level) {
    this->isChar = false;
    this->expReward = expReward; 
    this->LootDrop = mobLoots.getLootforMob(name); 

    vector<Effect*> effects;
    string effectDescription = "menyemburkan cairan asam pekat ke target, menyebabkan damage over time (kerusakan berkelanjutan) selama 3 turn";
    EffectHealth* heal = new EffectHealth("Heal", effectDescription, 3, 3, 1, healthRegen * getStats().getIntelligence() * 2);
    effects.push_back(heal);
    Skill *skill = new Skill("Heal", 3, 0, 5, attackDamage, effects);
    addSkill(skill);
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
        if ((rand() % 100 + 1) < loot.second * 100) {
            droppedItem.push_back(loot.first->cloneItem());  // buat salinan item    
        }
    }

    return droppedItem; 
}



void Mobs::reset() {
    currentHealth = maxHealth;
    currentMana = maxMana;
}