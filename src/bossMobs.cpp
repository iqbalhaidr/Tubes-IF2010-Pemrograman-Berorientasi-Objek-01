#include "bossMobs.hpp"

BossMobs::BossMobs(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int expReward)
 : Mobs(name, maxHealth, healthRegen, maxMana, manaRegen, attackDamage, strength, agility, intelligence, expReward, true) {
    this->onRage = false;
}

BossMobs::~BossMobs() {}

bool BossMobs::isOnRage() const {
    return onRage;
}


void BossMobs::reset() {
    Mobs::reset();
    onRage = false;
}