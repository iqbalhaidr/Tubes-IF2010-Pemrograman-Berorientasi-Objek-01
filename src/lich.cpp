#include "../include/lich.hpp"

Lich::Lich(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Lich", level, 14 + (level -1) * 1.2, 12 + (level -1) * 1.5, 36 + (level -1) * 2, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string poisonEffectDescription = "berpeluang 0.15 untuk memberikan damage dan mengurangi mana target selama 4 turn";
    EffectPoison* poisonEffect = new EffectPoison("Withering Touch (Poison)", poisonEffectDescription, 4, 4, 1, 2*getStats().getIntelligence());
    EffectManaReduc* manaReducEffect = new EffectManaReduc("Withering Touch", poisonEffectDescription, 4, 4, 10);
    effects.push_back(poisonEffect);
    effects.push_back(manaReducEffect);
    Skill *skill = new Skill("Withering Touch", 9, 0, 15, 2*getStats().getIntelligence(), effects);
    addSkill(skill);
}

Lich::~Lich() {}

void Lich::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getIntelligence());
}