#include "../include/slime.hpp"

Slime::Slime(int level, int expReward, Mobloot& mobLoots)
    : BasicMobs("Slime", level, 6 + (level - 1) * 0.6 , 11 + (level - 1) * 1.2,
                13 + (level - 1) * 1.5, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string effectDescription =
        "menyemburkan cairan asam pekat ke target, menyebabkan damage over "
        "time (kerusakan berkelanjutan) selama 3 turn";
    EffectPoison* DamageOverTime =
        new EffectPoison("Acidic Corrosion (Poison)", effectDescription, 3, 3,
                         1, attackDamage * getStats().getIntelligence() / 50);
    effects.push_back(DamageOverTime);
    Skill* skill =
        new Skill("Acidic Corrosion", 16, 0, 20, attackDamage, effects);
    addSkill(skill);
}

Slime::~Slime() {}

void Slime::updateBasicAttributes() {
    setAttackDamage(3 * getStats().getIntelligence() + getStats().getAgility());
}