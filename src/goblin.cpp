#include "goblin.hpp"

Goblin::Goblin(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage,  int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots)
 : BasicMobs(name, maxHealth, healthRegen, maxMana, manaRegen, attackDamage, strength, agility, intelligence, expReward, mobLoots) {
}

Goblin::~Goblin() {}