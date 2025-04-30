#ifndef CHARACTERS_HPP
#define CHARACTERS_HPP

#include "character.hpp"
#include "mage.hpp"
#include "assassin.hpp"
#include "fighter.hpp"
#include "berserker.hpp"
#include "necromancer.hpp"
#include <map>
#include <string>
#include <vector>

using namespace std;

class Characters {
private:
    map<string, Character*> characterMap;

public:
    Characters(const string& directory);
    ~Characters();

    void addCharacters(Character* Character);
    bool searchCharacter(const string& name) const;
    Character* getCharacterbyName(const string& Name);
    map<string, Character*> getCharacterMap() const { return characterMap; }

    void save(const string& directory) const;

};

#endif
