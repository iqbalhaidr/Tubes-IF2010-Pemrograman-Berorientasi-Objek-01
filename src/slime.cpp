#include "slime.hpp"

Slime::Slime(int level, int expReward, Mobloot& mobLoots)
 : BasicMobs("Slime", level, 6, 6, 16, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string effectDescription = "menyemburkan cairan asam pekat ke target, menyebabkan damage over time (kerusakan berkelanjutan) selama 3 turn";
    EffectPoison* DamageOverTime = new EffectPoison("Acidic Corrosion", effectDescription, 3, 3, 1, attackDamage * getStats().getIntelligence());
    effects.push_back(DamageOverTime);
    Skill *skill = new Skill("Acidic Corrosion", 0, 0, 0.2, attackDamage, effects);
    addSkill(skill);
}

Slime::~Slime() {}

void Slime::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getIntelligence());
}