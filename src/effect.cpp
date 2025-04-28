#include "../include/effect.hpp"

Effect::Effect(const std::string& name, const std::string& description, double duration, double remainingDuration)
    : name(name), description(description), duration(duration), remainingDuration(remainingDuration) {}

Effect::~Effect() {}

Effect::Effect(const Effect& other) 
    : name(other.name), description(other.description), duration(other.duration), remainingDuration(other.remainingDuration) {}

Effect& Effect::operator=(Effect& other) {
    name = other.name;
    description = other.description;
    duration = other.duration;
    remainingDuration = other.remainingDuration;
    return *this;
}

std::string Effect::getName() const {
    return name;
}

std::string Effect::getDescription() const {
    return description;
}   

double Effect::getDuration() const {
    return duration;
}

double Effect::getRemainingDuration() const {
    return remainingDuration;
}

void Effect::setName(const std::string& name) {
    this->name = name;
}

void Effect::setDescription(const std::string& description) {
    this->description = description;
}

void Effect::setDuration(double duration) {
    this->duration = duration;
}

void Effect::setRemainingDuration(double remainingDuration) {
    this->remainingDuration = remainingDuration;
}




bool Effect::isTurn() {
    return false;
}

bool Effect::isDamage() {
    return false;
}
bool Effect::isDefensive() {
    return false;
}

bool Effect::isTurnBased() {
    return false;
}