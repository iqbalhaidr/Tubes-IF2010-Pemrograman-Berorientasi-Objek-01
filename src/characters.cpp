#include "../include/characters.hpp"
#include "../include/exception.hpp"
#include <iterator>
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

        istringstream iss(line);
        vector<string> columns{istream_iterator<string>{iss}, istream_iterator<string>{}};

        if (columns.size() < 9) {
            throw InputOutputException("Format baris salah di file characters.txt");
        }
        try {
            string name = columns[0];
            int strength = stoi(columns[1]);
            int agility = stoi(columns[2]);
            int intelligence = stoi(columns[3]);
            int level = stoi(columns[4]);
            int exp = stoi(columns[5]);
            int gold = stoi(columns[6]);
            int masteryCost = stoi(columns[7]);
            string type = columns[8];
            vector<string> skillNames;
            for (int i = 9; i < columns.size(); i++) {
                if (i + 1 < columns.size() && columns[i].front() == '"' 
                    && columns[i+1].back() == '"') { // "Battle instinct" -> battle instinct
                    skillNames.push_back(columns[i].substr(1) + " " + columns[i+1].substr(0, columns[i+1].size() - 1));
                    i++; // longkap 1 elemen 
                } else if (columns[i].front() == '"' && columns[i].back() == '"') { // "Stormbreaker" -> stormbreaker
                    skillNames.push_back(columns[i].substr(1, columns[i].size() - 2));
                }
            }
            if (type == "Mage") {
                addCharacters(new Mage(name, strength, agility, intelligence, level, exp, gold, masteryCost, skillNames));
            } else if (type == "Assassin") {
                addCharacters(new Assassin(name, strength, agility, intelligence, level, exp, gold, masteryCost, skillNames));
            } else if (type == "Fighter") {
                addCharacters(new Fighter(name, strength ,agility ,intelligence ,level ,exp ,gold ,masteryCost, skillNames));
            } else if (type == "Berserker") {
                addCharacters(new Berserker(name, strength, agility, intelligence, level, exp, gold, masteryCost, skillNames));
            } else if (type == "Necromancer") {
                addCharacters(new Necromancer(name, strength, agility, intelligence, level, exp, gold, masteryCost, skillNames));
            } else {
                throw InputOutputException("Tipe karakter tidak valid");
            }
        } catch (const invalid_argument& e) {
            throw InputOutputException("Format angka tidak valid di file characters.txt");
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
void Characters::displayAvailableCharacters() {
    int counter = 1;
    for (const auto& pair : characterMap) {
        cout << counter << ". ";
        cout << pair.first << " - "; // nama char
        cout << pair.second->getType() << " - "; // tipe char
        cout << pair.second->getLevel() << endl; // level char
    }
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

        const vector<Skill*>& skills = c->getSkills();
        for (const Skill* skill : skills) {
            string skillName = skill->getName();
                skillName = "\"" + skillName + "\"";
            file << " " << skillName;
        }
        file << endl;

    
    }
    file.close();

 
}

