#include "lich.hpp"

Lich::Lich(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Lich", level, 14, 12, 36, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string stunEffectDescription = "berpeluang 0.5 untuk memberikan stun selama 1 turn";
    EffectTurn* stunEffect = new EffectTurn("Brutal Strike Stun", stunEffectDescription, 1, 1);
    // kurang chance buat stun
    // param skill damage dimana?
    Skill *skill = new Skill("Withering Touch", 0, 0, 0.15, effects);
    addSkill(skill);
}

Lich::~Lich() {}

void Lich::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getIntelligence());
}