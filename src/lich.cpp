#include "lich.hpp"

Lich::Lich(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Lich", level, 14, 12, 36, expReward, mobLoots) {
    Skill *skill = new Skill("Withering Touch", 0, 0, 0.15, "Withering Touch");
    addSkill(skill);
}

Lich::~Lich() {}

void Lich::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(4 * getStats().getIntelligence());
}