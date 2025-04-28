#include "skeleton.hpp"

Skeleton::Skeleton(int level, int expReward, Mobloot& mobLoots)
 : BasicMobs("Skeleton", level, 7, 8, 7, expReward, mobLoots) {
    Skill *skill = new Skill("Bone Shard", 0, 0, 0.25, "Bone Shard");
    addSkill(skill);
}

Skeleton::~Skeleton() {}

void Skeleton::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(4 * getStats().getStrength() + 4 * getStats().getAgility());
}