#include "darkKnight.hpp"

DarkKnight::DarkKnight(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Dark Knight", level, 20 + (level-1) * 1.8, 20 + (level-1) * 1.8, 16 + (level-1) * 1.2, expReward, mobLoots) {
    Skill *skill = new Skill("Soul Siphon", 0, 0, 0.35, "Soul Siphon");
    addSkill(skill);
}

DarkKnight::~DarkKnight() {}

void DarkKnight::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(3 * getStats().getStrength() + 3* getStats().getAgility());
}