#include "orc.hpp"

Orc::Orc(int level,  int expReward, Mobloot& mobLoots)
 : BasicMobs("Orc", level, 15, 8, 6, expReward, mobLoots) {
    Skill *skill = new Skill("Brutal Strike", 0, 0, 0.15, "Brutal Strike");
    addSkill(skill);
}

Orc::~Orc() {}

void Orc::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(4 * getStats().getStrength());
}