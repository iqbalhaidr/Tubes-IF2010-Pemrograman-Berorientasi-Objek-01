#include "../include/character.hpp"
#include <iostream>
using namespace std;

Character::Character(string name, int strength, int agility, int intelligence, int level, int exp, int gold, int masteryCost, vector<string> skillNames, string type)
: Unit(name, strength, agility, intelligence, level), 
    skillTree(type), exp(exp), gold(gold), masteryCost(masteryCost), type(type) {
    this->isChar = true;
    if (!skillNames.empty()) {
        loadCharacterSkills(skillNames);
    }
}

void Character::loadCharacterSkills(vector<string> skillNames) {
    vector<SkillNode*> roots = skillTree.getRoot();
    for (const string& skillName : skillNames) { // cek skill dengan skillname ada pada skilltree
        for (SkillNode* root : roots) {
            SkillNode* node = skillTree.getNodebyName(skillName, root);
            if (node == nullptr) {
                return;
            }
        }
    }

    for (SkillNode* root : roots) {
        bool hasRoot, hasLeft, hasRight = false;

        for (const string& skillName : skillNames) {
            if (root == nullptr && root->getSkill()->getName() == skillName) {
                hasRoot = true;
            } else if (root && root->getLeftNode() && root->getLeftSkill()->getName() == skillName) {
                hasLeft = true;
            } else if (root && root->getRightNode() && root->getRightSkill()->getName() == skillName) {
                hasRight = true;
            }
        }

        if ((!hasRoot && ((hasLeft && !hasRight) || (!hasLeft && hasRight))) 
            || (hasRoot && hasLeft && hasRight)) {
            return;
        }

        if (hasRoot && (hasLeft || hasRight)) {
            if (hasLeft) skillTree.currentSkills.push_back(root->getLeftNode());
            else if (hasRight) skillTree.currentSkills.push_back(root->getRightNode());
        } else if (!hasRoot && hasLeft && hasRight) {
            skillTree.currentSkills.push_back(root->getLeftNode());
            skillTree.currentSkills.push_back(root->getRightNode());

            auto it = find(skillTree.currentSkills.begin(), skillTree.currentSkills.end(), root);
            if (it != skillTree.currentSkills.end()) {
                skillTree.currentSkills.erase(it);
            }
        }

    }
    
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
    int counter = 1;
    for (SkillNode* skillNode : availableSkillNodes) {
        cout << to_string(counter) << ". " << skillNode->getSkill()->getName() << endl;
        counter++;
    }
}
void Character::upgradeSkill(string& skillNameToLearn) {
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
            throw MasteryCostNotEnough("masteryCost tidak cukup untuk mempelajari skill" + skillToLearn->getName());
            return;
        }
        masteryCost -= skillToLearn->getMasterCost();
        skillTree.upgradeSkill(parentNode, availableSkillNodes[idx]);
        addSkill(skillToLearn);

        bool canRemove = parentNode->canRemove();
        if (canRemove) {
            removeSkill(parentNode->getSkill()); //hapus vektor skill char
            for (auto it = skillTree.currentSkills.begin(); it != skillTree.currentSkills.end(); ) {
                if ((*it)->getSkill()->getName() == parentNode->getSkill()->getName()) {
                    it = skillTree.currentSkills.erase(it);  //hapus vektor currentskill di skilltree
                } else {
                    ++it;
                }
            }
            
        }
    } else {
        throw InvalidSkill("skill tidak available untuk di-upgrade");
    }

}

void Character::displayCharacter() {
    cout << "\n===== PROFIL CHARACTER =====\n\n";
    cout << "Character Name : " << this->name << endl;
    cout << "Type           : " << this->type << endl;
    cout << "Level          : " << this->level << endl;
    cout << "-> STATS, HEALTH, MANA \n";
    cout << "Strength : " << this->getStats().getStrength() << " , ";
    cout << "Agility : " << this->getStats().getStrength() << " , ";
    cout << "Intelligence : " << this->getStats().getStrength() << endl;
    cout << "Current Health :" << this->currentHealth << endl;
    cout << "Current Mana :" << this->currentMana << endl;
    cout << "<-\n";
    cout << "Exp : " << this->exp << endl;
    cout << "Gold : " << this->gold << endl;
    cout << "Mastery Cost : " << this->masteryCost << endl;
    cout << "Skills : [";
    for (int i = 0; i < skills.size(); i++) {
        cout << skills[i]->getName();
        if (i < skills.size() - 1) {
            cout << ",";
        }
    }
    cout << "]\n";
}
void Character::reset() {
    currentHealth = maxHealth;
    currentMana = maxMana;
    activeEffects.clear(); 
}
