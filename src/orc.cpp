#include "orc.hpp"

Orc::Orc(int level,  int expReward, Mobloot& mobLoots)
 : BasicMobs("Orc", level, 15, 8, 6, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string stunEffectDescription = "berpeluang 0.5 untuk memberikan stun selama 1 turn";
    EffectTurn* stunEffect = new EffectTurn("Brutal Strike Stun", stunEffectDescription, 1, 1);
    // kurang chance buat stun
    // param skill damage dimana?
    effects.push_back(stunEffect);
    Skill *skill = new Skill("Brutal Strike", 0, 0, 0.15, effects);
    addSkill(skill);
}

Orc::~Orc() {}

void Orc::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getStrength());
}