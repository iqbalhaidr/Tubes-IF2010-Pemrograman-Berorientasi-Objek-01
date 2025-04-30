#include "../include/darkKnight.hpp"

DarkKnight::DarkKnight(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Dark Knight", level, 20, 20, 16, expReward, mobLoots) {
    //efek lifesteal 
    updateBasicAttributes();
    vector<Effect*> effects;
    string lifeStealEffectDescription = "berpeluang 0.35 untuk melakukan lifesteal pada turn selanjutnya";
    EffectHealth* lifeStealEffect = new EffectHealth("Brutal Strike Life Steal", lifeStealEffectDescription, 1, 1, 0.8, 0.3*2*getStats().getIntelligence());
    // kurang chance buat lifesteal
    // param skill damage dimana?
    effects.push_back(lifeStealEffect);
    Skill *skill = new Skill("Soul Siphon", 0, 0, 35, 2*getStats().getIntelligence(),effects);
    addSkill(skill);
}

DarkKnight::~DarkKnight() {}

void DarkKnight::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getStrength() + 4* getStats().getAgility());
}