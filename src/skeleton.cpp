#include "../include/skeleton.hpp"

Skeleton::Skeleton(int level, int expReward, Mobloot& mobLoots)
 : BasicMobs("Skeleton", level, 7, 8, 7, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string healthEffectDescription = "berpeluang 0.25 untuk memberikan damage fisik tambahan pada serangan selanjutnya";
    EffectDamage* stunEffect = new EffectDamage("Brittle", healthEffectDescription, 1, 1, 1, 10);
    // kurang chance buat stun
    // param skill damage dimana?
    effects.push_back(stunEffect);
    Skill *skill = new Skill("Bone Shard", 0, 0, 25,attackDamage, effects);
    addSkill(skill);
}

Skeleton::~Skeleton() {}

void Skeleton::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getStrength() + 4 * getStats().getAgility());
}