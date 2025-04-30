#include "lich.hpp"

Lich::Lich(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Lich", level, 14, 12, 36, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string poisonEffectDescription = "berpeluang 0.15 untuk memberikan damage dan mengurangi mana target selama 4 turn";
    EffectPoison* poisonEffect = new EffectPoison("Withering Touch", poisonEffectDescription, 4, 4, 1, 2*getStats().getIntelligence());
    EffectManaReduc* manaReducEffect = new EffectManaReduc("Withering Touch", poisonEffectDescription, 4, 4, 10);
    // kurang chance buat stun
    // param skill damage dimana?
    effects.push_back(poisonEffect);
    effects.push_back(manaReducEffect);
    Skill *skill = new Skill("Withering Touch", 0, 0, 15, effects);
    addSkill(skill);
}

Lich::~Lich() {}

void Lich::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getIntelligence());
}