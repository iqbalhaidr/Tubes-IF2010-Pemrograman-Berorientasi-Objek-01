#include "../include/basicMobs.hpp"

BasicMobs::BasicMobs(string name, int level, int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots)
 : Mobs(name, level, strength, agility, intelligence, expReward, false, mobLoots) {
}

BasicMobs::~BasicMobs() {}
