#include "ogre.hpp"

Ogre::Ogre(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Ogre", level, 32 + (level-1) * 2, 16 + (level-1) * 1.5, 12 + (level-1) * 1.2, expReward, mobLoots) {
    Skill *skill = new Skill("Pulverize", 0, 0, 0.3, "Pulverize");
    addSkill(skill);
}

Ogre::~Ogre() {}

void Ogre::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getStrength());
}

// void Ogre::useSkill(string skill, Unit& target) {}

