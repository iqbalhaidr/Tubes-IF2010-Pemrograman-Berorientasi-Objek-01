#ifndef SKILLTREE
#define SKILLTREE
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
        SkillNode(const SkillNode& other) = default;
        SkillNode& operator=(const SkillNode& other);

        SkillNode* getLeftNode() const;
        SkillNode* getRightNode() const;
        Skill* getLeftSkill() const;
        Skill* getRightSkill() const;
    
};

#endif