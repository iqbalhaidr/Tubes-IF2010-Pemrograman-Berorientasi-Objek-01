#include "../include/characters.hpp"
#include "../include/exception.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

Characters::Characters(const string& directory) {
    string filename = directory + "characters.txt";
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        throw InputOutputException("Directory tidak ditemukan");
    }

    ifstream file(filename);
    if (file.fail()) {
        throw InputOutputException("File characters.txt tidak ditemukan");
    }

    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        string name, type;
        int strength, agility, intelligence;
        int level, exp, gold, masteryCost;

        if (ss >> name >> strength >> agility >> intelligence >> level >> exp >> gold >> masteryCost >> type) {
            if (type == "Mage") {
                if (ss.fail()) throw InputOutputException("Format baris salah di file characters.txt untuk Mage");
                addCharacters(new Mage(name, strength, agility, intelligence, level, exp, gold, masteryCost));
            } else if (type == "Assassin") {
                if (ss.fail()) throw InputOutputException("Format baris salah di file characters.txt untuk Assassin");
                addCharacters(new Assassin(name, strength, agility, intelligence, level, exp, gold, masteryCost));
            } else if (type == "Fighter") {
                if (ss.fail()) throw InputOutputException("Format baris salah di file characters.txt untuk Fighter");
                addCharacters(new Fighter(name, strength ,agility ,intelligence ,level ,exp ,gold ,masteryCost));
            } else if (type == "Berserker") {
                if (ss.fail()) throw InputOutputException("Format baris salah di file characters.txt untuk Berserker");
                addCharacters(new Berserker(name, strength, agility, intelligence, level, exp, gold, masteryCost));
            } else if (type == "Necromancer") {
                if (ss.fail()) throw InputOutputException("Format baris salah di file characters.txt untuk Necromancer");
                addCharacters(new Necromancer(name, strength, agility, intelligence, level, exp, gold, masteryCost));
            } else {
                throw InputOutputException("Tipe karakter tidak valid");
            }
        } else {
            throw InputOutputException("Format baris salah di file characters.txt");
        }
    }   
}

Characters::~Characters() {
    for (auto& character : characterMap) {
        delete character.second;
    }
    characterMap.clear();
}

void Characters::addCharacters(Character* character) {
    auto it = characterMap.find(character->getName());
    if (it != characterMap.end()) {
        delete character;
        throw CharactersError("Character dengan nama yang sama sudah ada");
    }
    characterMap[character->getName()] = character;
}

bool Characters::searchCharacter(const string& name) const {
    return characterMap.find(name) != characterMap.end();
}

Character* Characters::getCharacterbyName(const string& name) {
    auto it = characterMap.find(name);
    if (it != characterMap.end()) {
        return it->second;
    }
    return nullptr;
}

void Characters::save(const string& directory) const {
    ofstream file(directory + "characters.txt");

    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        throw InventoryEror("Directory tidak ditemukan");
    }

    for (const auto& character : characterMap) {
        Character* c = character.second;
        file << c->getName() << " "
            << c->getStats().getStrength() << " "
            << c->getStats().getAgility() << " " 
            << c->getStats().getIntelligence() << " "
            << c->getLevel() << " "              
            << c->getExp() << " "
            << c->getGold() << " "
            << c->getMasteryCost() << " "
            << c->getType();
        file << endl;
    
    }
    file.close();

 
}

