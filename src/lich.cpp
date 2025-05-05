#include "../include/lich.hpp"

Lich::Lich(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Lich", level, 14 + (level -1) * 1.2, 12 + (level -1) * 1.7, 36 + (level -1) * 2, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string poisonEffectDescription = "memberikan damage sihir gelap secara terus-menerus (menggunakan INT) selama 4 turn dan juga mengurangi mana pemain";
    EffectPoison* poisonEffect = new EffectPoison("Withering Touch (Poison)", poisonEffectDescription, 4, 4, 100, 2*getStats().getIntelligence(), true);
    EffectManaReduc* manaReducEffect = new EffectManaReduc("Withering Touch (ManaReduc)", poisonEffectDescription, 4, 4, 8, 100, true);
    effects.push_back(poisonEffect);
    effects.push_back(manaReducEffect);
    Skill *skill = new Skill("Withering Touch", 9, 0, 15, 2*getStats().getIntelligence(), effects);
    addSkill(skill);
}

Lich::~Lich() {}

void Lich::updateBasicAttributes() {
    setAttackDamage(5 * getStats().getIntelligence() + 2 * getStats().getAgility());
}