#include "demonLord.hpp"

DemonLord::DemonLord(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Demon Lord", level, 16 + (level-1) * 1.2, 32 + (level-1) * 2, 16 + (level-1) * 1.5, expReward, mobLoots) {
    Skill *skill = new Skill("Infernal Curse", 0, 0, 0.15, "Infernal Curse");
    addSkill(skill);
}

DemonLord::~DemonLord() {}

void DemonLord::updateBasicAttributes() {
    setAttackDamage(4* getStats().getAgility());
}