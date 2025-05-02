#include "../include/demonLord.hpp"

DemonLord::DemonLord(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Demon Lord", level, 16 + (level -1) * 1.2, 32 + (level -1) * 2, 16 + (level -1) * 1.5, expReward, mobLoots) {
    //
    updateBasicAttributes();
    vector<Effect*> effects;
    string debuffEffectDescription = "berpeluang 0.15 untuk memberikan kutukan yang mengurangi attack power dan defense power selama 5 turn";
    EffectDamage* attackDebuff = new EffectDamage("Infernal Curse", debuffEffectDescription, 5, 5, 1, -10);
    EffectDefensive* defenseDebuff = new EffectDefensive("Infernal Curse", debuffEffectDescription, 5, 5, 1, 10, 0);
    effects.push_back(attackDebuff);
    effects.push_back(defenseDebuff);
    Skill *skill = new Skill("Infernal Curse", 8, 0, 15, 0, effects);
    addSkill(skill);
}

DemonLord::~DemonLord() {}

void DemonLord::updateBasicAttributes() {
    setAttackDamage(4* getStats().getAgility());
}