#include "demonLord.hpp"

DemonLord::DemonLord(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Demon Lord", level, 16, 32, 16, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string stunEffectDescription = "berpeluang 0.5 untuk memberikan stun selama 1 turn";
    EffectTurn* stunEffect = new EffectTurn("Brutal Strike Stun", stunEffectDescription, 1, 1);
    // kurang chance buat stun
    // param skill damage dimana?
    Skill *skill = new Skill("Infernal Curse", 0, 0, 15, "Infernal Curse");
    addSkill(skill);
}

DemonLord::~DemonLord() {}

void DemonLord::updateBasicAttributes() {
    setAttackDamage(4* getStats().getAgility());
}