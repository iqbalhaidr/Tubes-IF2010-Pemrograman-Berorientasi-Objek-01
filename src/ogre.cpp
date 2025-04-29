#include "ogre.hpp"

Ogre::Ogre(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Ogre", level, 32, 16, 12, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string critEffectDescription = "memberikan damage fisik yang sangat besar (2.5x attack biasa)";
    EffectDamage* critDamage = new EffectDamage("Pulverize Critical", critEffectDescription, 1, 1, 1, attackDamage * 2.5);
    string stunEffectDescription = "memiliki peluang tinggi (0.9 effect chance) untuk menyebabkan efek stun selama 1 turn";
    EffectTurn* stunEffect = new EffectTurn("Pulverize Stun", stunEffectDescription, 1, 1);
    // kurang chance buat stun
    effects.push_back(critDamage);
    effects.push_back(stunEffect);
    Skill *skill = new Skill("Pulverize", 0, 0, 0.3, effects);
    addSkill(skill);
}

Ogre::~Ogre() {}

void Ogre::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getStrength());
}

// void Ogre::useSkill(string skill, Unit& target) {}

