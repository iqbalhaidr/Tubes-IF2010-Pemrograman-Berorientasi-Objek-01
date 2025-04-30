#include "demonLord.hpp"

DemonLord::DemonLord(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Demon Lord", level, 16, 32, 16, expReward, mobLoots) {
    //
    updateBasicAttributes();
    vector<Effect*> effects;
    string debuffEffectDescription = "berpeluang 0.15 untuk memberikan kutukan yang mengurangi attack power dan defense power selama 5 turn";
    EffectReducePower* attackReducEffect = new EffectReducePower("Infernal Curse", debuffEffectDescription, 5, 5, 1, 10);
    EffectManaReduc* manaReducEffect = new EffectManaReduc("Infernal Curse", debuffEffectDescription, 5, 5, 10);
    // kurang chance buat stun
    // param skill damage dimana?
    effects.push_back(attackReducEffect);
    effects.push_back(manaReducEffect);
    Skill *skill = new Skill("Infernal Curse", 0, 0, 15, 0, effects);
    addSkill(skill);
}

DemonLord::~DemonLord() {}

void DemonLord::updateBasicAttributes() {
    setAttackDamage(4* getStats().getAgility());
}