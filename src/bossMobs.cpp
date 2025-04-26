#include "bossMobs.hpp"

BossMobs::BossMobs(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots)
 : Mobs(name, maxHealth, healthRegen, maxMana, manaRegen, attackDamage, strength, agility, intelligence, expReward, mobLoots) {
    this->rageUsed = false;
}

BossMobs::~BossMobs() {}

bool BossMobs::isRageUsed() const {
    return rageUsed;
}

void BossMobs::rage() {
    if (!isRageUsed()) {
        setStats(getStats().getStrength() * 1.5, getStats().getAgility() * 1.5, getStats().getIntelligence() * 1.5);
        rageUsed = true;
    }
}

void BossMobs::reset() {
    Mobs::reset();
    rageUsed = false;
}