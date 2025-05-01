#include "../include/skillNode.hpp"

SkillNode::SkillNode(Skill* skill) : skill(skill){
    left = nullptr;
    right = nullptr;
}


SkillNode::SkillNode(Skill* skill, SkillNode* left, SkillNode* right) : skill(skill), left(left), right(right) {}

SkillNode::~SkillNode() {
    delete skill;
    delete left;
    delete right;
}

SkillNode::SkillNode(const SkillNode& other): skill(new Skill(*other.skill)) {
    if (other.left == nullptr){
        left = nullptr;
    } else {
        left = new SkillNode(*other.left);
    } 

    if (other.right == nullptr){
        right = nullptr;
    } else {
        right = new SkillNode(*other.right);
    }
}

SkillNode& SkillNode::operator=(const SkillNode& other) {
    delete skill;
    delete left;
    delete right;

    skill = new Skill(*other.skill);
    if (other.left == nullptr){
        left = nullptr;
    } else {
        left = new SkillNode(*other.left);
    } 

    if (other.right == nullptr){
        right = nullptr;
    } else {
        right = new SkillNode(*other.right);
    }

    return *this;
}

SkillNode::~SkillNode(){
    delete skill;
}

Skill* SkillNode::getLeftSkill() const {
    return left->skill;
}

Skill* SkillNode::getRightSkill() const {
    return right->skill;
}

SkillNode* SkillNode::getLeftNode() const {
    return left;
}

SkillNode* SkillNode::getRightNode() const {
    return right;
}


Skill* SkillNode::getSkill() const {
    return skill;
}
void SkillNode::setLeftNode(SkillNode* left) {
    this->left = left;
}

void SkillNode::setRightNode(SkillNode* right) {
    this->right = right;
}

bool SkillNode::canRemove() const {
    return left->unlocked && right->unlocked;
}