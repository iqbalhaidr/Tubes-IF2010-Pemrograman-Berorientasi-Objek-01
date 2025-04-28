#include "darkKnight.hpp"

DarkKnight::DarkKnight(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Dark Knight", level, 20, 20, 16, expReward, mobLoots) {
    Skill *skill = new Skill("Soul Siphon", 0, 0, 0.35, "Soul Siphon");
    addSkill(skill);
}

DarkKnight::~DarkKnight() {}

void DarkKnight::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(4 * getStats().getStrength() + 4* getStats().getAgility());
}