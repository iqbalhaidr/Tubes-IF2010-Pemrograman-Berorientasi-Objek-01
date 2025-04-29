#include "skeleton.hpp"

Skeleton::Skeleton(int level, int expReward, Mobloot& mobLoots)
 : BasicMobs("Skeleton", level, 7, 8, 7, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string stunEffectDescription = "berpeluang 0.5 untuk memberikan stun selama 1 turn";
    EffectTurn* stunEffect = new EffectTurn("Brutal Strike Stun", stunEffectDescription, 1, 1);
    // kurang chance buat stun
    // param skill damage dimana?
    Skill *skill = new Skill("Bone Shard", 0, 0, 0.25, effects);
    addSkill(skill);
}

Skeleton::~Skeleton() {}

void Skeleton::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getStrength() + 4 * getStats().getAgility());
}