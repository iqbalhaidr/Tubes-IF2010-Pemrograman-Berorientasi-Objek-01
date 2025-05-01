#ifndef SKILLTREE_CPP
#define SKILLTREE_CPP
#include "skillNode.hpp"
#include <string>
#include <vector>

class SkillTree{
    private:
        SkillNode* root1;
        SkillNode* root2;
        SkillNode* root3;
        string char_type;

    public:
        SkillTree(string char_type);
        ~SkillTree();
        void destroy(SkillNode*);
        vector<Skill*> getAvailableUpgrade() const;  
        void upgradeSkill(int skill_awal, bool isLeft);      
        void upgradeSkill(Skill skill_awal, Skill skill_baru);      
        void upgradeSkill(Skill* skill_awal, Skill* skill_baru);      
        
};

#endif