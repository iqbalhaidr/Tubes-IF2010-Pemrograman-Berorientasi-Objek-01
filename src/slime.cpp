#include "slime.hpp"

Slime::Slime(int level, int expReward, Mobloot& mobLoots)
 : BasicMobs("Slime", level, 6 + (level-1) * 1.2, 6 + (level-1) * 1.5, 16 + (level-1) * 2, expReward, mobLoots) {

    Skill *skill = new Skill("Acidic Corrosion", 0, 0, 0.2, "Acidic Corrosion");
    addSkill(skill);
}

Slime::~Slime() {}

void Slime::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getIntelligence());
}