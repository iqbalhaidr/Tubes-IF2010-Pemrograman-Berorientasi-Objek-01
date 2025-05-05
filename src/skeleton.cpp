#include "../include/skeleton.hpp"

Skeleton::Skeleton(int level, int expReward, Mobloot& mobLoots)
 : BasicMobs("Skeleton", level, 11 + (level -1) * 1.4, 9 + (level -1) * 0.7, 7 + (level -1) * 1.3, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string damageEffectDesc = "berpeluang 0.25 untuk memberikan damage fisik tambahan pada serangan selanjutnya";
    EffectDamage* buffDamage = new EffectDamage("Brittle (Damage)", damageEffectDesc, 1, 1, 1, 100, false);
    effects.push_back(buffDamage);
    Skill *skill = new Skill("Bone Shard", 15, 0, 25, attackDamage, effects);
    addSkill(skill);
}

Skeleton::~Skeleton() {}

void Skeleton::updateBasicAttributes() {
    setAttackDamage(2 * getStats().getStrength() + 2 * getStats().getAgility());
}