#include "../include/character.hpp"
#include <iostream>
using namespace std;

Character::Character(string name, int strength, int agility, int intelligence, int level, int exp, int gold, int masteryCost, string type)
: Unit(name, strength, agility, intelligence, level), skillTree(type) {
    std::cout << "Character constructor called" << std::endl;
    setExp(exp);
    setGold(gold);
    setMasteryCost(masteryCost);
    setType(type);
}

Character::~Character() {}

int Character::getExp() const { return exp;}
int Character::getGold() const { return gold;}
int Character::getMasteryCost() const { return masteryCost;}
string Character::getType() const { return type;}
SkillTree Character::getSkillTree() const { return skillTree;}

void Character::setLevel(int level) { this->level = level;}
void Character::setExp(int exp) { this->exp = exp;}
void Character::setGold(int gold) { this->gold = gold;}
void Character::setMasteryCost(int masteryCost) { this->masteryCost = masteryCost;}
void Character::setType(string type) { this->type = type;}
void Character::displayAvailableSkillUpgrades() {
    vector<SkillNode*> availableSkillNodes;
    skillTree.getAvailableUpgrade(availableSkillNodes);
    int counter = 0;
    for (SkillNode* skillNode : availableSkillNodes) {
        cout << to_string(counter) << ". " << skillNode->getSkill()->getName() << endl;
        counter++;
    }
}
void Character::UpgradeSkill(string& skillNameToLearn) {
    bool found = false;
    vector<SkillNode*> availableSkillNodes;
    int idx = 0;
    skillTree.getAvailableUpgrade(availableSkillNodes);
    for (int i = 0; i < availableSkillNodes.size(); i++) {
        if (availableSkillNodes[i]->getSkill()->getName() == skillNameToLearn) {
            found = true;
            idx = i;
        }
    }
    
    if (found) {
        Skill* skillToLearn = availableSkillNodes[idx]->getSkill();
        SkillNode* parentNode = skillTree.getParent(*(availableSkillNodes[idx]->getSkill()));
        if (masteryCost < availableSkillNodes[idx]->getSkill()->getMasterCost()) {
            cout << "masteryCost tidak cukup untuk mempelajari skill" << skillToLearn->getName() << endl;
            return;
        }
        masteryCost -= skillToLearn->getMasterCost();
        skillTree.upgradeSkill(parentNode, availableSkillNodes[idx]);
        addSkill(skillToLearn);

        bool canRemove = parentNode->canRemove();
        if (canRemove) {
            removeSkill(parentNode->getSkill());
        }
    }

}

void Character::reset() {
    currentHealth = maxHealth;
    currentMana = maxMana;
    activeEffects.clear(); 
}
