#include "goblin.hpp"

Goblin::Goblin(int level, int expReward, Mobloot& mobLoots)
 : BasicMobs("Goblin", level, 7 + (level-1) * 1.2, 15 + (level-1) * 2, 6 + (level-1) * 1.5, expReward, mobLoots) {
    Skill *skill = new Skill("Sneaky Stab", 0, 0, 0.2, "Sneaky Stab");
    addSkill(skill);
}

Goblin::~Goblin() {}

void Goblin::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(4 * getStats().getAgility());
}