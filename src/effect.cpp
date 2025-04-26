#include "../include/effect.hpp"

Effect::Effect(const std::string& name, const std::string& description, double duration, double remainingDuration)
    : name(name), description(description), duration(duration), remainingDuration(remainingDuration) {}

Effect::~Effect() {}

Effect::Effect(Effect& other) 
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