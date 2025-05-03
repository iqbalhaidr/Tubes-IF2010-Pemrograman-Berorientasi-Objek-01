#include "../include/stats.hpp"

Stats::Stats(int strength, int agility, int intelligence) 
    : strength(strength), agility(agility), intelligence(intelligence) {}

Stats::~Stats() {}

int Stats::getStrength() const { return strength;}
int Stats::getAgility() const { return agility;}
int Stats::getIntelligence() const { return intelligence;}

void Stats::setStrength(int strength) { this->strength = strength;}
void Stats::setAgility(int agility) { this->agility = agility;}
void Stats::setIntelligence(int intelligence) { this->intelligence = intelligence;}