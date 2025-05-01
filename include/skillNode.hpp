#ifndef SKILLNODE
#define SKILLNODE
#include "skill.hpp"
#include "EffectDamage.hpp"
#include "EffectDefensive.hpp"
#include "EffectHealth.hpp"
#include "EffectHealthRegen.hpp"
#include "EffectManaReduc.hpp"
#include "EffectManaRegen.hpp"
#include "EffectPoison.hpp"
#include "EffectTurn.hpp"

class SkillNode{
    private:
        Skill* skill;
        SkillNode* left;
        SkillNode* right;
    public:
        SkillNode(Skill* skill);
        SkillNode(Skill* skill, SkillNode* left, SkillNode* right);
        ~SkillNode();
        SkillNode(const SkillNode& other);
        SkillNode& operator=(const SkillNode& other);

        Skill* getSkill() const;
        SkillNode* getLeftNode() const;
        SkillNode* getRightNode() const;
        Skill* getLeftSkill() const;
        Skill* getRightSkill() const;
        void setLeftNode(SkillNode* left);
        void setRightNode(SkillNode* right);
    
};

#endif