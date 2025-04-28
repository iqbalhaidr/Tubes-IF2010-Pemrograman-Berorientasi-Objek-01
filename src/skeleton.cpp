#include "skeleton.hpp"

Skeleton::Skeleton(int level, int expReward, Mobloot& mobLoots)
 : BasicMobs("Skeleton", level, 7, 8, 7, expReward, mobLoots) {
}

Skeleton::~Skeleton() {}

void Skeleton::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(4 * getStats().getStrength() + 4 * getStats().getAgility());
}