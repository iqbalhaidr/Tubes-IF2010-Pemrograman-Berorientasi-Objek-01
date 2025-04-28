#include "orc.hpp"

Orc::Orc(int level,  int expReward, Mobloot& mobLoots)
 : BasicMobs("Orc", level, 15 + (level-1) * 2, 8 + (level-1) * 1.5, 6 + (level-1) * 1.2, expReward, mobLoots) {
    Skill *skill = new Skill("Brutal Strike", 0, 0, 0.15, "Brutal Strike");
    addSkill(skill);
}

Orc::~Orc() {}

void Orc::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(4 * getStats().getStrength());
}