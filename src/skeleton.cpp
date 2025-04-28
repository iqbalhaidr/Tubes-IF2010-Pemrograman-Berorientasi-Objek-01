#include "skeleton.hpp"

Skeleton::Skeleton(int level, int expReward, Mobloot& mobLoots)
 : BasicMobs("Skeleton", level, 7 + (level-1) * 1.8, 8 + (level-1) * 1.8, 7 + (level-1) * 1.2, expReward, mobLoots) {
    Skill *skill = new Skill("Bone Shard", 0, 0, 0.25, "Bone Shard");
    addSkill(skill);
}

Skeleton::~Skeleton() {}

void Skeleton::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(3 * getStats().getStrength() + 3 * getStats().getAgility());
}