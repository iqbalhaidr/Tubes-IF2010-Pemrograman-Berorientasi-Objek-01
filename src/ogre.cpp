#include "../include/ogre.hpp"

Ogre::Ogre(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Ogre", level, 32 + (level -1) * 2.3, 16 + (level -1) * 1.3, 12 + (level -1) * 1, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string stunEffectDescription = "berpeluang 0.5 untuk memberikan stun selama 1 turn";
    EffectTurn* stunEffect = new EffectTurn("Pulverize (Stun)", stunEffectDescription, 1, 1, 90, true);
    effects.push_back(stunEffect);
    Skill *skill = new Skill("Pulverize", 10, 0, 30, attackDamage * 2.5, effects);
    addSkill(skill);
}

Ogre::~Ogre() {}

void Ogre::updateBasicAttributes() {
    setAttackDamage(7 * getStats().getStrength());
}


