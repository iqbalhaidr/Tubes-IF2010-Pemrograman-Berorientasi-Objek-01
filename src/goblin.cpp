#include "goblin.hpp"

Goblin::Goblin(int level, int expReward, Mobloot& mobLoots)
 : BasicMobs("Goblin", level, 7, 15, 6, expReward, mobLoots) {
    Skill *skill = new Skill("Sneaky Stab", 0, 0, 0.2, "Sneaky Stab");
    addSkill(skill);
}

Goblin::~Goblin() {}

void Goblin::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(4 * getStats().getAgility());
}