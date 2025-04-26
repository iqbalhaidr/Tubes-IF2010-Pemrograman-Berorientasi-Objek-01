#include "lich.hpp"

Lich::Lich(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots)
 : BossMobs(name, maxHealth, healthRegen, maxMana, manaRegen, attackDamage, strength, agility, intelligence, expReward, mobLoots) {
}

Lich::~Lich() {}