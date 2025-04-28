#include "lich.hpp"

Lich::Lich(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Lich", level, 14, 12, 36, expReward, mobLoots) {
}

Lich::~Lich() {}

void Lich::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(4 * getStats().getIntelligence());
}