#include "demonLord.hpp"

DemonLord::DemonLord(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Demon Lord", level, 16, 32, 16, expReward, mobLoots) {
    Skill *skill = new Skill("Infernal Curse", 0, 0, 0.15, "Infernal Curse");
    addSkill(skill);
}

DemonLord::~DemonLord() {}

void DemonLord::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(4* getStats().getAgility());
}