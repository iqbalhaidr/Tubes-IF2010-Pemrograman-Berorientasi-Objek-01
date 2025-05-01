#include "../include/skill.hpp" 

Skill::Skill(const std::string& name, double manaCost, double masterCost, double skillChance, double damage, vector<Effect*> effects)
    : name(name), manaCost(manaCost), masterCost(masterCost), skillChance(skillChance), effects(effects), damage(damage) {}

Skill::~Skill() {}

Skill::Skill(Skill& other) 
    : name(other.name), manaCost(other.manaCost), masterCost(other.masterCost), skillChance(other.skillChance), effects(effects) {}

Skill& Skill::operator=(Skill& other){
    name = other.name;
    manaCost = other.manaCost;
    masterCost = other.masterCost;
    skillChance = other.skillChance;
    effects = other.effects;

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

double Skill::getskillChance() const {
    return skillChance;
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

void Skill::setskillChance(double skillChance) {
    this->skillChance = skillChance;
}

void Skill::setDamage(double damage) {
    this->damage = damage;
}

std::vector<Effect*> Skill::getEffects() const {
    return effects;
}

void Skill::setEffects(std::vector<Effect*> effects) {
    this->effects = effects;
}

bool Skill::operator==(const Skill& other) const {
    return name == other.name;
}