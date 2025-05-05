#include "../include/bossMobs.hpp"

BossMobs::BossMobs(string name, int level, int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots)
 : Mobs(name, level, strength, agility, intelligence, expReward, mobLoots), 
    rageUsed(false) {
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

bool BossMobs::isBoss() {
    return true;
}
void BossMobs::reset() {
    Mobs::reset();
    rageUsed = false;
}