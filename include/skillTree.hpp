#ifndef SKILLTREE
#define SKILLTREE
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
        vector<SkillNode*> getAvailableUpgrade() const;  
        void upgradeSkill(SkillNode* skill_awal, SkillNode* skill_baru);      
        SkillNode* getParent(Skill child);
        vector<SkillNode*> getRoot() const;
        SkillNode* getNodebyName(string name, SkillNode* root) const;

};

#endif