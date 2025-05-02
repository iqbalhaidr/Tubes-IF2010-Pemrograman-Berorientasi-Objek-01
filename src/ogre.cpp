#include "../include/ogre.hpp"

Ogre::Ogre(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Ogre", level, 32 + (level -1) * 2, 16 + (level -1) * 1.5, 12 + (level -1) * 1.2, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string stunEffectDescription = "berpeluang 0.5 untuk memberikan stun selama 1 turn";
    EffectTurn* stunEffect = new EffectTurn("Pulverize", stunEffectDescription, 1, 1, 0.9);
    effects.push_back(stunEffect);
    Skill *skill = new Skill("Pulverize", 10, 0, 30, attackDamage * 2.5, effects);
    addSkill(skill);
}

Ogre::~Ogre() {}

void Ogre::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getStrength());
}


