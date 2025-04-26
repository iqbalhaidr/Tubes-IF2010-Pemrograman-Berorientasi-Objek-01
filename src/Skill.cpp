#include "../include/skill.hpp" 

Skill::Skill(const std::string& name, double manaCost, double masterCost, double effectChance, const std::string& effectType)
    : name(name), manaCost(manaCost), masterCost(masterCost), effectChance(effectChance) {}

Skill::~Skill() {}

Skill::Skill(Skill& other) 
    : name(other.name), manaCost(other.manaCost), masterCost(other.masterCost), effectChance(other.effectChance) {}

Skill& Skill::operator=(Skill& other){
    name = other.name;
    manaCost = other.manaCost;
    masterCost = other.masterCost;
    effectChance = other.effectChance;

    return *this;
}

std::string Skill::getName() const {
    return name;
}

double Skill::getManaCost() const {
    return manaCost;
}

double Skill::getMasterCost() const {
    return masterCost;
}

double Skill::getEffectChance() const {
    return effectChance;
}

double Skill::getDamage() const {
    return damage;
}

void Skill::setName(const std::string& name) {
    this->name = name;
}

void Skill::setManaCost(double manaCost) {
    this->manaCost = manaCost;
}

void Skill::setMasterCost(double masterCost) {
    this->masterCost = masterCost;
}

void Skill::setEffectChance(double effectChance) {
    this->effectChance = effectChance;
}

void Skill::setDamage(double damage) {
    this->damage = damage;
}
