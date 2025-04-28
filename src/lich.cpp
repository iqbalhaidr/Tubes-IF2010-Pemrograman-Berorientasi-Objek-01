#include "lich.hpp"

Lich::Lich(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Lich", level, 14 + (level-1) * 1.2, + (level-1) * 1.5, 36 + (level-1) * 2, expReward, mobLoots) {
    Skill *skill = new Skill("Withering Touch", 0, 0, 0.15, "Withering Touch");
    addSkill(skill);
}

Lich::~Lich() {}

void Lich::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(4 * getStats().getIntelligence());
}