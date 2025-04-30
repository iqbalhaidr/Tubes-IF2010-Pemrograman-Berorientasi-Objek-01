#include "ogre.hpp"

Ogre::Ogre(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Ogre", level, 32, 16, 12, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string stunEffectDescription = "berpeluang 0.5 untuk memberikan stun selama 1 turn";
    EffectTurn* stunEffect = new EffectTurn("Pulverize", stunEffectDescription, 1, 1, 0.9);
    effects.push_back(stunEffect);
    Skill *skill = new Skill("Pulverize", 0, 0, 30, attackDamage * 2.5, effects);
    addSkill(skill);
}

Ogre::~Ogre() {}

void Ogre::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getStrength());
}

// void Ogre::useSkill(string skill, Unit& target) {}

