#include "goblin.hpp"

Goblin::Goblin(int level, int expReward, Mobloot& mobLoots)
 : BasicMobs("Goblin", level, 7, 15, 6, expReward, mobLoots) {
}

Goblin::~Goblin() {}

void Goblin::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(4 * getStats().getAgility());
}