#include "darkKnight.hpp"

DarkKnight::DarkKnight(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Dark Knight", level, 20, 20, 16, expReward, mobLoots) {
}

DarkKnight::~DarkKnight() {}

void DarkKnight::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(4 * getStats().getStrength() + 4* getStats().getAgility());
}