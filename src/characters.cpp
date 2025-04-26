#include "characters.hpp"
#include "exception.hpp"
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
        string name, type, mastery;
        int maxHealth, healthRegen, maxMana, manaRegen, attackDamage, strength, agility, intelligence, level, exp, gold;
        double summonChance; // Untuk Necromancer
        double extraMana; // Untuk Mage
        double blockChance; // Untuk Fighter
        int rageMultiplier; // Untuk Berserker
        double criticalChance; // Untuk Assassin
        int criticalMultiplier; // Untuk Assassin

        if (ss >> name >> type >> maxHealth >> healthRegen >> maxMana >> manaRegen >> attackDamage >> strength >> agility >> intelligence >> level >> exp >> gold) {
            if (type == "Mage") {
                ss >> extraMana;
                if (ss.fail()) throw InputOutputException("Format baris salah di file characters.txt untuk Mage");
                addCharacters(new Mage(name, maxHealth, healthRegen, maxMana, manaRegen, attackDamage, strength, agility, intelligence, level, exp, gold, extraStat));
            } else if (type == "Assassin") {
                ss >> criticalChance >> criticalMultiplier;
                if (ss.fail()) throw InputOutputException("Format baris salah di file characters.txt untuk Assassin");
                addCharacters(new Assassin(name, maxHealth, healthRegen, maxMana, manaRegen, attackDamage, strength, agility, intelligence, level, exp, gold, criticalChance / 100.0f * 100.0f , criticalMultiplier));
            } else if (type == "Fighter") {
                ss >> blockChance;
                if (ss.fail()) throw InputOutputException("Format baris salah di file characters.txt untuk Fighter");
                addCharacters(new Fighter(name,maxHealth ,healthRegen ,maxMana ,manaRegen ,attackDamage ,strength ,agility ,intelligence ,level ,exp ,gold ,mastery));
            } else if (type == "Berserker") {
                ss >> rageMultiplier;
                if (ss.fail()) throw InputOutputException("Format baris salah di file characters.txt untuk Berserker");
                addCharacters(new Berserker(name, maxHealth, healthRegen, maxMana, manaRegen, attackDamage, strength, agility, intelligence, level, exp, gold, rageMultiplier));
            } else if (type == "Necromancer") {
                ss >> summonChance;
                if (ss.fail()) throw InputOutputException("Format baris salah di file characters.txt untuk Necromancer");
                addCharacters(new Necromancer(name, maxHealth, healthRegen, maxMana, manaRegen, attackDamage, strength, agility, intelligence, level, exp, mastery, gold, extraStat));
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

    file << "#<name><type> <maxHealth> <healthRegen> <maxMana> <manaRegen> [<atk> <str> <agi> <int>] <level> <exp> <gold> [type_specific_data]\n";
    
    for (const auto& character : characterMap) {
        Character* c = character.second;
        file << c->getName() << " "
            c->getType() << " "
            c->getMaxHealth() << " "
            c->getHealthRegen() << " "
            c->getMaxMana() << " "
            c->getManaRegen() << " "
            c->getAttackDamage() << " "
            c->getStats().getStrength() << " "
            c->getStats().getAgility() << " " 
            c->getStats().getIntelligence() << " "
            c->getLevel() << " "              
            c->getExp() << " "
            c->getGold() << " ";
        //BELUM SELESAI
        if (c->getType() == "Mage") {
            Mage* mage = dynamic_cast<Mage*>(c);
            if (mage) file << " " << m->getExtraMana();
        } else if (c->getType() == "Assassin") {
            Assassin* assassin = dynamic_cast<Assassin*>(c);
            if (assassin) file << " " << assassin->getCriticalChance() * 100.0f << " " << assassin->getCriticalMultiplier();
        } else if (c->getType() == "Fighter") {
            Fighter* fighter = dynamic_cast<Fighter*>(c);
            if (fighter) file << " " << fighter->getBlockChance();
        } else if (c->getType() == "Berserker") {
            Berserker* berserker = dynamic_cast<Berserker*>(c);
            if (berserker) file << " " << berserker->getRageMultiplier();
        } else if (c->getType() == "Necromancer") {
            Necromancer* necromancer = dynamic_cast<Necromancer*>(c);
            if (necromancer) file << " " << necromancer->getSummonChance();
        } else {
            throw InputOutputException("ada Tipe character tidak valid");
        }
        file << endl;
    
    }
    file.close();

 
}

