#include "darkKnight.hpp"

DarkKnight::DarkKnight(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Dark Knight", level, 20, 20, 16, expReward, mobLoots) {
    //efek lifesteal 
    updateBasicAttributes();
    vector<Effect*> effects;
    string stunEffectDescription = "berpeluang 0.5 untuk memberikan stun selama 1 turn";
    EffectTurn* stunEffect = new EffectTurn("Brutal Strike Stun", stunEffectDescription, 1, 1);
    // kurang chance buat stun
    // param skill damage dimana?
    effects.push_back(stunEffect);
    Skill *skill = new Skill("Soul Siphon", 0, 0, 35, effects);
    addSkill(skill);
}

DarkKnight::~DarkKnight() {}

void DarkKnight::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getStrength() + 4* getStats().getAgility());
}