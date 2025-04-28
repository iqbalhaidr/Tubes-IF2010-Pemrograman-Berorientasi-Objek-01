#include "ogre.hpp"

Ogre::Ogre(int level, int expReward, Mobloot& mobLoots)
 : BossMobs("Ogre", level, 32, 16, 12, expReward, mobLoots) {
}

Ogre::~Ogre() {}

void Ogre::updateBasicAttributes() {
    Unit::updateBasicAttributes();
    setAttackDamage(4 * getStats().getStrength());
}

// void Ogre::useSkill(string skill, Unit& target) {}

