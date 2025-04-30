#ifndef SKILLTREE_CPP
#define SKILLTREE_CPP
#include "skillNode.hpp"
#include <string>

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
        
        
};

#endif