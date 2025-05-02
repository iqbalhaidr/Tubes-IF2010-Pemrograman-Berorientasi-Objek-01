#include "../include/darkKnight.hpp"

DarkKnight::DarkKnight(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Dark Knight", level, 20 + (level -1) * 1.8, 20 + (level -1) * 1.8, 16 + (level -1) * 1.2, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string lifeStealEffectDescription = "berpeluang 0.35 untuk melakukan lifesteal pada turn selanjutnya (effect, 0.8 chance)";
    EffectHealth* lifeStealEffect = new EffectHealth("Brutal Strike Life Steal", lifeStealEffectDescription, 1, 1, 0.8, 0.3*2*getStats().getIntelligence());
    effects.push_back(lifeStealEffect);
    Skill *skill = new Skill("Soul Siphon", 10, 0, 35, 2*getStats().getIntelligence(), effects);
    addSkill(skill);
}

DarkKnight::~DarkKnight() {}

void DarkKnight::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getStrength() + 4* getStats().getAgility());
}