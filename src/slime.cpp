#include "slime.hpp"

Slime::Slime(int level, int expReward, Mobloot& mobLoots)
 : BasicMobs("Slime", level, 6, 6, 16, expReward, mobLoots) {
}

Slime::~Slime() {}

void Slime::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(4 * getStats().getIntelligence());
}