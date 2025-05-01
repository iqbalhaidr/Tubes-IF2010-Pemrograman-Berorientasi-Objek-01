#include "../include/skillTree.hpp"

SkillTree::SkillTree(string char_type){
    if (char_type == "Fighter") {
        //Fighter
        // Defensive effects
        EffectDefensive* damageReduction = dynamic_cast<EffectDefensive*>(Effect::createEffect("Armor"));

        EffectDefensive* damageReductionPlusPlus = dynamic_cast<EffectDefensive*>(Effect::createEffect("Armor"));
        damageReductionPlusPlus->setDefense(damageReductionPlusPlus->getDefense() * 2);

        EffectDefensive* damageReductionPlus = dynamic_cast<EffectDefensive*>(Effect::createEffect("Armor"));
        damageReductionPlus->setDefense(damageReductionPlus->getDefense() * 1.5);

        EffectHealthRegen* healthRegenPlus = dynamic_cast<EffectHealthRegen*>(Effect::createEffect("Obay"));
        healthRegenPlus->setHealAmount(healthRegenPlus->getHealAmount() * 1.5);

        // Skill1
        Skill* f1_1 = new Skill("Stone Skin", 10, 0, 0.5, 0, {damageReduction});
        Skill* f1_2 = new Skill("Divine Shield", 10, 0, 0.5, 0, {damageReductionPlusPlus});
        Skill* f1_3 = new Skill("Guardian's Oath", 10, 0, 0.5, 0, {damageReductionPlus, healthRegenPlus});

        // Poison effects (Bleed, Burn)
        EffectPoison* Bleed = dynamic_cast<EffectPoison*>(Effect::createEffect("Bleed"));
        EffectPoison* BleedPlus = dynamic_cast<EffectPoison*>(Effect::createEffect("Bleed"));
        BleedPlus->setDamage(BleedPlus->getDamage() * 1.5);
        EffectPoison* BleedPlusPlus = dynamic_cast<EffectPoison*>(Effect::createEffect("Bleed"));
        BleedPlusPlus->setDamage(BleedPlusPlus->getDamage() * 2);

        EffectPoison* BurnPlus = dynamic_cast<EffectPoison*>(Effect::createEffect("Burn"));
        BurnPlus->setDamage(BurnPlus->getDamage() * 1.5);

        // Skill2
        Skill* f2_1 = new Skill("Fighter Fist", 10, 0, 0.5, 0, {Bleed});
        Skill* f2_2 = new Skill("Bloodfire Strike", 10, 0, 0.5, 0, {BleedPlus, BurnPlus});
        Skill* f2_3 = new Skill("Crimson Onslaught", 10, 0, 0.5, 0, {BleedPlusPlus});

        // Damage and support effects
        EffectDamage* CriticalChance = dynamic_cast<EffectDamage*>(Effect::createEffect("Critical"));

        EffectDamage* CriticalChancePlus = dynamic_cast<EffectDamage*>(Effect::createEffect("Critical"));
        CriticalChancePlus->setDamage(CriticalChancePlus->getDamage() * 1.5);

        EffectManaRegen* manaRegenPlus = dynamic_cast<EffectManaRegen*>(Effect::createEffect("Kukubima"));
        manaRegenPlus->setManaAmount(manaRegenPlus->getManaAmount() * 1.5);

        EffectTurn* StunChancePlus = dynamic_cast<EffectTurn*>(Effect::createEffect("Stun chance"));
        StunChancePlus->setChance(StunChancePlus->getChance() * 1.5);

        // Skill3
        Skill* f3_1 = new Skill("Battle Instinct", 10, 0, 0.5, 0, {CriticalChance});
        Skill* f3_2 = new Skill("Spirit Rampage", 10, 0, 0.5, 0, {CriticalChancePlus, manaRegenPlus});
        Skill* f3_3 = new Skill("Stormbreaker", 10, 0, 0.5, 0, {CriticalChancePlus, StunChancePlus});

        root1 = new SkillNode(f1_1);
        root1->setLeftNode(new SkillNode(f1_2));
        root1->setRightNode(new SkillNode(f1_3));
        
        root2 = new SkillNode(f2_1);
        root2->setLeftNode(new SkillNode(f2_2));
        root2->setRightNode(new SkillNode(f2_3));
        
        root3 = new SkillNode(f3_1);
        root3->setLeftNode(new SkillNode(f3_2));
        root3->setRightNode(new SkillNode(f3_3));
        

    }
    if (char_type == "Mage") {
        // Mage skill1
        EffectPoison* Burn = dynamic_cast<EffectPoison*>(Effect::createEffect("Burn"));
        EffectPoison* BurnPlus = dynamic_cast<EffectPoison*>(Effect::createEffect("Burn"));
        BurnPlus->setDamage(BurnPlus->getDamage() * 1.5);
        EffectDamage* CriticalPlus = dynamic_cast<EffectDamage*>(Effect::createEffect("Critical"));
        CriticalPlus->setDamage(CriticalPlus->getDamage() * 1.5);
        EffectTurn* StunPlus = dynamic_cast<EffectTurn*>(Effect::createEffect("Stun"));
        StunPlus->setChance(StunPlus->getChance() * 1.5);

        Skill* m1_1 = new Skill("Fire Arrow", 10, 0, 0.5, 0, {Burn});
        Skill* m1_2 = new Skill("Meteor Strike", 10, 0, 0.5, 0, {BurnPlus, CriticalPlus});
        Skill* m1_3 = new Skill("Indra's Wrath", 10, 0, 0.5, 0, {StunPlus, BurnPlus});

        // Mage skill2
        EffectTurn* Disable = dynamic_cast<EffectTurn*>(Effect::createEffect("Disable"));
        EffectTurn* DisablePlus = dynamic_cast<EffectTurn*>(Effect::createEffect("Disable"));
        DisablePlus->setChance(DisablePlus->getChance() * 1.5);
        EffectManaRegen* manaRegenPlus = dynamic_cast<EffectManaRegen*>(Effect::createEffect("Kukubima"));
        manaRegenPlus->setManaAmount(manaRegenPlus->getManaAmount() * 1.5);
        EffectHealthRegen* healthRegenPlus = dynamic_cast<EffectHealthRegen*>(Effect::createEffect("Obay"));
        healthRegenPlus->setHealAmount(healthRegenPlus->getHealAmount() * 1.5);

        Skill* m2_1 = new Skill("Chains of Ruin", 10, 0, 0.5, 0, {Disable});
        Skill* m2_2 = new Skill("Mana Prison", 10, 0, 0.5, 0, {DisablePlus, manaRegenPlus});
        Skill* m2_3 = new Skill("Vampiric Chains", 10, 0, 0.5, 0, {DisablePlus, healthRegenPlus});

        // Mage skill3
        EffectManaRegen* manaRegenPlusPlus = dynamic_cast<EffectManaRegen*>(Effect::createEffect("Kukubima"));
        manaRegenPlusPlus->setManaAmount(manaRegenPlusPlus->getManaAmount() * 2);

        Skill* m3_1 = new Skill("Mana Spring", 10, 0, 0.5, 0, {manaRegenPlusPlus});
        
        root1 = new SkillNode(m1_1);
        root1->setLeftNode(new SkillNode(m1_2));
        root1->setRightNode(new SkillNode(m1_3));

        root2 = new SkillNode(m2_1);
        root2->setLeftNode(new SkillNode(m2_2));
        root2->setRightNode(new SkillNode(m2_3));

        root3 = new SkillNode(m3_1);
        // done
    
    }

    else if (char_type == "Assassin") {
        // Assassin skill1
        EffectPoison* Bleed = dynamic_cast<EffectPoison*>(Effect::createEffect("Bleed"));
        EffectPoison* BleedPlus = dynamic_cast<EffectPoison*>(Effect::createEffect("Bleed"));
        BleedPlus->setDamage(BleedPlus->getDamage() * 1.5);
        EffectPoison* BleedPlusPlus = dynamic_cast<EffectPoison*>(Effect::createEffect("Bleed"));
        BleedPlusPlus->setDamage(BleedPlusPlus->getDamage() * 2);
        EffectDamage* CriticalPlus = dynamic_cast<EffectDamage*>(Effect::createEffect("Critical"));
        CriticalPlus->setDamage(CriticalPlus->getDamage() * 1.5);

        Skill* a1_1 = new Skill("Silent Cut", 10, 0, 0.5, 0, {Bleed});
        Skill* a1_2 = new Skill("Crimson Fang", 10, 0, 0.5, 0, {BleedPlus, CriticalPlus});
        Skill* a1_3 = new Skill("Sanguine Requiem", 10, 0, 0.5, 0, {BleedPlusPlus});

        // Assassin skill2
        EffectTurn* StunPlusPlus = dynamic_cast<EffectTurn*>(Effect::createEffect("Stun"));
        StunPlusPlus->setChance(StunPlusPlus->getChance() * 2);

        Skill* a2_1 = new Skill("Silent Ambush", 10, 0, 0.5, 0, {StunPlusPlus});

        // Assassin skill3
        EffectHealthRegen* healthRegenPlusPlus = dynamic_cast<EffectHealthRegen*>(Effect::createEffect("Obay"));
        healthRegenPlusPlus->setHealAmount(healthRegenPlusPlus->getHealAmount() * 2);

        Skill* a3_1 = new Skill("Blood Pact", 10, 0, 0.5, 0, {healthRegenPlusPlus});

        root1 = new SkillNode(a1_1);
        root1->setLeftNode(new SkillNode(a1_2));
        root1->setRightNode(new SkillNode(a1_3));

        root2 = new SkillNode(a2_1);
        
        root3 = new SkillNode(a3_1);
    }

    else if (char_type == "Necromancer") {
        // Necromancer skill1
        EffectHealthRegen* healthRegen = dynamic_cast<EffectHealthRegen*>(Effect::createEffect("Obay"));
        EffectHealthRegen* healthRegenPlus = dynamic_cast<EffectHealthRegen*>(Effect::createEffect("Obay"));
        healthRegenPlus->setHealAmount(healthRegenPlus->getHealAmount() * 1.5);
        EffectManaRegen* manaRegenPlus = dynamic_cast<EffectManaRegen*>(Effect::createEffect("Kukubima"));
        manaRegenPlus->setManaAmount(manaRegenPlus->getManaAmount() * 1.5);
        EffectManaRegen* manaRegenPlusPlus = dynamic_cast<EffectManaRegen*>(Effect::createEffect("Kukubima"));
        manaRegenPlusPlus->setManaAmount(manaRegenPlusPlus->getManaAmount() * 2);

        Skill* n1_1 = new Skill("Soul Feast", 10, 0, 0.5, 0, {healthRegen});
        Skill* n1_2 = new Skill("Ghoul's Renewal", 10, 0, 0.5, 0, {healthRegenPlus, manaRegenPlus});
        Skill* n1_3 = new Skill("Necrotic Wellspring", 10, 0, 0.5, 0, {manaRegenPlusPlus});

        // Necromancer skill2
        EffectPoison* PoisonPlusPlus = dynamic_cast<EffectPoison*>(Effect::createEffect("Poison"));
        PoisonPlusPlus->setDamage(PoisonPlusPlus->getDamage() * 2);

        Skill* n2_1 = new Skill("Plague Surge", 10, 0, 0.5, 0, {PoisonPlusPlus});

        // Necromancer skill3
        EffectTurn* StunPlusPlus = dynamic_cast<EffectTurn*>(Effect::createEffect("Stun"));
        StunPlusPlus->setChance(StunPlusPlus->getChance() * 2);

        Skill* n3_1 = new Skill("Soul Paralysis", 10, 0, 0.5, 0, {StunPlusPlus});
    
        root1 = new SkillNode(n1_1);
        root1->setLeftNode(new SkillNode(n1_2));
        root1->setRightNode(new SkillNode(n1_3));

        root2 = new SkillNode(n2_1);

        root3 = new SkillNode(n3_1);
    }

    else if (char_type == "Berserker") {
        // Berserk skill1
        EffectDamage* Critical = dynamic_cast<EffectDamage*>(Effect::createEffect("Critical"));
        EffectDamage* CriticalPlusPlus = dynamic_cast<EffectDamage*>(Effect::createEffect("Critical"));
        CriticalPlusPlus->setDamage(CriticalPlusPlus->getDamage() * 2);
        EffectDamage* CriticalPlus = dynamic_cast<EffectDamage*>(Effect::createEffect("Critical"));
        CriticalPlus->setDamage(CriticalPlus->getDamage() * 1.5);
        EffectTurn* Disable = dynamic_cast<EffectTurn*>(Effect::createEffect("Disable"));

        Skill* b1_1 = new Skill("Fury Strike", 10, 0, 0.5, 0, {Critical});
        Skill* b1_2 = new Skill("Bloodthirst Awakening", 10, 0, 0.5, 0, {CriticalPlusPlus});
        Skill* b1_3 = new Skill("Crippling Rampage", 10, 0, 0.5, 0, {CriticalPlus, Disable});

        // Berserk skill2
        EffectDefensive* damageReductionPlusPlus = dynamic_cast<EffectDefensive*>(Effect::createEffect("Armor"));
        damageReductionPlusPlus->setDefense(damageReductionPlusPlus->getDefense() * 2);

        Skill* b2_1 = new Skill("Indomitable Fury", 10, 0, 0.5, 0, {damageReductionPlusPlus});

        // Berserk skill3
        EffectHealthRegen* healthRegenPlusPlus = dynamic_cast<EffectHealthRegen*>(Effect::createEffect("Obay"));
        healthRegenPlusPlus->setHealAmount(healthRegenPlusPlus->getHealAmount() * 2);

        Skill* b3_1 = new Skill("Blood Renewal", 10, 0, 0.5, 0, {healthRegenPlusPlus});

        root1 = new SkillNode(b1_1);
        root1->setLeftNode(new SkillNode(b1_2));
        root1->setRightNode(new SkillNode(b1_3));

        root2 = new SkillNode(b2_1);

        root3 = new SkillNode(b3_1);
    }

    currentSkills.push_back(root1);
    currentSkills.push_back(root2);
    currentSkills.push_back(root3);
}

SkillTree::~SkillTree() {
    destroy(root1);
    destroy(root2);
    destroy(root3);
}

void SkillTree::destroy(SkillNode* node) {
    if (node == nullptr){return;}
    destroy(node->getLeftNode());
    destroy(node->getRightNode());
    delete node;
}

std::vector<SkillNode*> SkillTree::getAvailableUpgrade(vector<SkillNode*>& result) const{
    for (int i = 0; i < currentSkills.size(); i++){

            if (currentSkills[i]->getLeftNode() != nullptr){
                if (currentSkills[i]->getLeftNode()->unlocked == false){
                    result.push_back(currentSkills[i]->getLeftNode());
                }
                if (currentSkills[i]->getRightNode()->unlocked == false){
                    result.push_back(currentSkills[i]->getRightNode());
                }
            }
        }
        return result;
}

void SkillTree::upgradeSkill(SkillNode* skill_awal, SkillNode* skill_baru){
    skill_baru->unlocked = true;
    currentSkills.push_back(skill_baru);
}


SkillNode* SkillTree::getParent(Skill child) {
    for (int i = 0; i < currentSkills.size(); i++){
        if (currentSkills[i]->getLeftSkill()->getName() == child.getName()){
            return currentSkills[i];
        }
        if (currentSkills[i]->getRightSkill()->getName() == child.getName()){
            return currentSkills[i];
        }
    }
    return nullptr;
}