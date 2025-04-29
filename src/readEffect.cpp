#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
// #include <../include/effect.hpp>
#include "../include/effect.hpp"
#include "../include/EffectDamage.hpp"
// #include "../include/EffectDefensive.hpp"
// #include "../include/EffectTurnBased.hpp"

int main(){
    Effect* effect;
    std::ifstream EffectFile("../config/effect.txt");
    std::string line = "";

    if (!EffectFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }


    std::getline(EffectFile, line);

    while (std::getline(EffectFile, line)){
        std::istringstream iss(line);
        std::string type;
        std::string name;
        std::string description;
        double duration;
        double amount;
        int chance;

        // TYPE
        iss >> type;
        std::cout << "Type: " << type << std::endl;

        
        // NAME
        iss >> name;
        std::cout << "name: " << name << std::endl;
        
        // DESCRIPTION
        
        iss >> description;
        
        std::string temp;
        
        while (description[description.size()-1] != '>'){
            iss >> temp;
            description += " " + temp;
        }
        
        description = description.substr(1, description.size()-2);
        std::cout << "Desc: " << description << std::endl;
        
        // Duration
        iss >> duration;
        std::cout << "duration: " << duration << std::endl;
        
        //Amount
        iss >> amount;
        std::cout << "amount: " << amount << std::endl;
        
        //Chance
        iss >> chance;
        std::cout << "chance: " << chance << std::endl;
        

        if (type == "EffectDamage"){
            effect = new EffectDamage(name, description, duration, duration, chance, amount);   
            // std::cout << "Effect Damage" << std::endl;
        }

        std::cout<< "Name: " <<effect->getName() << std::endl;
    }
}