#include "../include/effect.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/EffectDamage.hpp"
#include "../include/EffectDefensive.hpp"
#include "../include/EffectHealthRegen.hpp"
#include "../include/EffectManaRegen.hpp"
#include "../include/EffectHealth.hpp"
#include "../include/EffectPoison.hpp"
#include "../include/EffectTurn.hpp"

Effect::Effect(const std::string& name, const std::string& description, double duration, double remainingDuration, int chance, bool isThrowable)
    : name(name), description(description), duration(duration), remainingDuration(remainingDuration), chance(chance) {}

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

int Effect::getChance(){
    return chance;
}

void Effect::setChance(int chance){
    this->chance = chance;
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


void Effect::remove(Unit* unit) {
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

bool Effect::isHealthRegen() {
    return false;
}

bool Effect::isManaRegen() {
    return false;
}
bool Effect::isThrowable() {
    return lempar;
}

bool Effect::isPoison() {
    return false;
}

bool Effect::isHealth() {
    return false;
}

bool Effect::isManaReduc() {
    return false;
}

bool Effect::isReducePower() {
    return false;
}

bool Effect::operator==(const Effect& other) const{
    return name == other.name && description == other.description && duration == other.duration && remainingDuration == other.remainingDuration;
}

void Effect::decreaseRemainingDuration(){
    remainingDuration = remainingDuration - 1;
}

Effect* Effect::createEffect(const std::string& nama) {
    std::ifstream EffectFile("../data/effect.txt");
    std::string line = "";
    
    std::string type;
    std::string name = "";
    std::string description;
    double duration;
    double amount;
    int chance;
    bool lempar;
    std::string lempar_str;

    if (!EffectFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return nullptr;
    }

    
    while (name != nama && std::getline(EffectFile, line)){
        std::istringstream iss(line);
        iss >> type;
        // std::cout << "Type: " << type << std::endl;
        
        
        // NAME
        iss >> name;
        // std::cout << "name: " << name << std::endl;
    }
    
    std::istringstream iss(line);
    // iss >> description;
    // std::cout<< "Desc: " << description << std::endl;
    if (name == nama){
        iss >> type;
        iss >> name;
        iss >> description;
        
        std::string temp;
        
        while (description[description.size()-1] != '>'){

            iss >> temp;
            description += " " + temp;
        }

        description = description.substr(1, description.size()-2);

        
        // Duration
        iss >> duration;
        // std::cout << "duration: " << duration << std::endl;
        
        //Amount
        iss >> amount;
        // std::cout << "amount: " << amount << std::endl;
        
        //Chance
        iss >> chance;

        iss >> lempar_str;
        // std::cout << "chance: " << chance << std::endl;
        if (lempar_str == "true"){
            lempar = true;
        }
        else{
            lempar = false;
        }
    }

   if (type == "EffectDamage"){
        return new EffectDamage(name, description, duration, duration, chance, amount, lempar);
    }
    //    TO DO: FIX EFFECT DEFENSIVE PARAMETER
    else if (type == "EffectDefensive"){
        return new EffectDefensive(name, description, duration, duration, chance, amount, amount, lempar);
   }
   else if (type == "EffectHealthRegen"){
        int temp = (int)amount;
        return new EffectHealthRegen(name, description, duration, duration, temp, chance, lempar);
   }
   else if (type == "EffectManaRegen"){
        return new EffectManaRegen(name, description, duration, duration, amount, chance, lempar);
   }
   else if (type == "EffectHealth"){
        return new EffectHealth(name, description, duration, duration, chance, amount, lempar);
   }
   else if (type == "EffectPoison"){
        return new EffectPoison(name, description, duration, duration, chance, amount, lempar);
   }
   else if (type == "EffectTurn"){
        return new EffectTurn(name, description, duration, duration, chance, lempar);
    }

    else{
        std::cout<<"Effect not found" << std::endl;
        return nullptr;
    }

}

