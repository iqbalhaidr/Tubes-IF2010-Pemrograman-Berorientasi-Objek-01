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
        vector<SkillNode*> currentSkills;
        SkillTree(string char_type);
        ~SkillTree();
        void destroy(SkillNode*);
        vector<SkillNode*> getAvailableUpgrade(vector<SkillNode*>& res) const;  
        void upgradeSkill(SkillNode* skill_awal, SkillNode* skill_baru);      
        SkillNode* getParent(Skill child);

};

#endif