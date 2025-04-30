#include "../include/skillTree.hpp"

SkillTree::SkillTree(string char_type){
    if (char_type == "Fighter") {
        //Fighter
        // Defensive effects
        EffectDefensive* damageReduction = dynamic_cast<EffectDefensive*>(Effect::createEffect("damage reduction"));

        EffectDefensive* damageReductionPlusPlus = dynamic_cast<EffectDefensive*>(Effect::createEffect("damage reduction"));
        damageReductionPlusPlus->setDefense(damageReductionPlusPlus->getDefense() * 2);

        EffectDefensive* damageReductionPlus = dynamic_cast<EffectDefensive*>(Effect::createEffect("damage reduction"));
        damageReductionPlus->setDefense(damageReductionPlus->getDefense() * 1.5);

        EffectHealthRegen* healthRegenPlus = dynamic_cast<EffectHealthRegen*>(Effect::createEffect("health regen"));
        healthRegenPlus->setHealAmount(healthRegenPlus->getHealAmount() * 1.5);

        // Skill1
        Skill* f1_1 = new Skill("Stone Skin", 10, 0, 0.5, 0, {damageReduction});
        Skill* f1_2 = new Skill("Divine Shield", 10, 0, 0.5, 0, {damageReductionPlusPlus});
        Skill* f1_3 = new Skill("Guardian's Oath", 10, 0, 0.5, 0, {damageReductionPlus, healthRegenPlus});

        // Poison effects (bleed, burn)
        EffectPoison* bleed = dynamic_cast<EffectPoison*>(Effect::createEffect("bleed"));
        EffectPoison* bleedPlus = dynamic_cast<EffectPoison*>(Effect::createEffect("bleed"));
        bleedPlus->setDamage(bleedPlus->getDamage() * 1.5);
        EffectPoison* bleedPlusPlus = dynamic_cast<EffectPoison*>(Effect::createEffect("bleed"));
        bleedPlusPlus->setDamage(bleedPlusPlus->getDamage() * 2);

        EffectPoison* burnPlus = dynamic_cast<EffectPoison*>(Effect::createEffect("burn"));
        burnPlus->setDamage(burnPlus->getDamage() * 1.5);

        // Skill2
        Skill* f2_1 = new Skill("Fighter Fist", 10, 0, 0.5, 0, {bleed});
        Skill* f2_2 = new Skill("Bloodfire Strike", 10, 0, 0.5, 0, {bleedPlus, burnPlus});
        Skill* f2_3 = new Skill("Crimson Onslaught", 10, 0, 0.5, 0, {bleedPlusPlus});

        // Damage and support effects
        EffectDamage* criticalChance = dynamic_cast<EffectDamage*>(Effect::createEffect("critical chance"));

        EffectDamage* criticalChancePlus = dynamic_cast<EffectDamage*>(Effect::createEffect("critical chance"));
        criticalChancePlus->setDamage(criticalChancePlus->getDamage() * 1.5);

        EffectManaRegen* manaRegenPlus = dynamic_cast<EffectManaRegen*>(Effect::createEffect("mana regen"));
        manaRegenPlus->setManaAmount(manaRegenPlus->getManaAmount() * 1.5);

        EffectTurn* stunChancePlus = dynamic_cast<EffectTurn*>(Effect::createEffect("stun chance"));
        stunChancePlus->setChance(stunChancePlus->getChance() * 1.5);

        // Skill3
        Skill* f3_1 = new Skill("Battle Instinct", 10, 0, 0.5, 0, {criticalChance});
        Skill* f3_2 = new Skill("Spirit Rampage", 10, 0, 0.5, 0, {criticalChancePlus, manaRegenPlus});
        Skill* f3_3 = new Skill("Stormbreaker", 10, 0, 0.5, 0, {criticalChancePlus, stunChancePlus});

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
        EffectPoison* burn = dynamic_cast<EffectPoison*>(Effect::createEffect("burn"));
        EffectPoison* burnPlus = dynamic_cast<EffectPoison*>(Effect::createEffect("burn"));
        burnPlus->setDamage(burnPlus->getDamage() * 1.5);
        EffectDamage* criticalPlus = dynamic_cast<EffectDamage*>(Effect::createEffect("critical"));
        criticalPlus->setDamage(criticalPlus->getDamage() * 1.5);
        EffectTurn* stunPlus = dynamic_cast<EffectTurn*>(Effect::createEffect("stun"));
        stunPlus->setChance(stunPlus->getChance() * 1.5);

        Skill* m1_1 = new Skill("Fire Arrow", 10, 0, 0.5, 0, {burn});
        Skill* m1_2 = new Skill("Meteor Strike", 10, 0, 0.5, 0, {burnPlus, criticalPlus});
        Skill* m1_3 = new Skill("Indra's Wrath", 10, 0, 0.5, 0, {stunPlus, burnPlus});

        // Mage skill2
        EffectTurn* disable = dynamic_cast<EffectTurn*>(Effect::createEffect("disable"));
        EffectTurn* disablePlus = dynamic_cast<EffectTurn*>(Effect::createEffect("disable"));
        disablePlus->setChance(disablePlus->getChance() * 1.5);
        EffectManaRegen* manaRegenPlus = dynamic_cast<EffectManaRegen*>(Effect::createEffect("mana regen"));
        manaRegenPlus->setManaAmount(manaRegenPlus->getManaAmount() * 1.5);
        EffectHealthRegen* healthRegenPlus = dynamic_cast<EffectHealthRegen*>(Effect::createEffect("health regen"));
        healthRegenPlus->setHealAmount(healthRegenPlus->getHealAmount() * 1.5);

        Skill* m2_1 = new Skill("Chains of Ruin", 10, 0, 0.5, 0, {disable});
        Skill* m2_2 = new Skill("Mana Prison", 10, 0, 0.5, 0, {disablePlus, manaRegenPlus});
        Skill* m2_3 = new Skill("Vampiric Chains", 10, 0, 0.5, 0, {disablePlus, healthRegenPlus});

        // Mage skill3
        EffectManaRegen* manaRegenPlusPlus = dynamic_cast<EffectManaRegen*>(Effect::createEffect("mana regen"));
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
        EffectPoison* bleed = dynamic_cast<EffectPoison*>(Effect::createEffect("bleed"));
        EffectPoison* bleedPlus = dynamic_cast<EffectPoison*>(Effect::createEffect("bleed"));
        bleedPlus->setDamage(bleedPlus->getDamage() * 1.5);
        EffectPoison* bleedPlusPlus = dynamic_cast<EffectPoison*>(Effect::createEffect("bleed"));
        bleedPlusPlus->setDamage(bleedPlusPlus->getDamage() * 2);
        EffectDamage* criticalPlus = dynamic_cast<EffectDamage*>(Effect::createEffect("critical"));
        criticalPlus->setDamage(criticalPlus->getDamage() * 1.5);

        Skill* a1_1 = new Skill("Silent Cut", 10, 0, 0.5, 0, {bleed});
        Skill* a1_2 = new Skill("Crimson Fang", 10, 0, 0.5, 0, {bleedPlus, criticalPlus});
        Skill* a1_3 = new Skill("Sanguine Requiem", 10, 0, 0.5, 0, {bleedPlusPlus});

        // Assassin skill2
        EffectTurn* stunPlusPlus = dynamic_cast<EffectTurn*>(Effect::createEffect("stun"));
        stunPlusPlus->setChance(stunPlusPlus->getChance() * 2);

        Skill* a2_1 = new Skill("Silent Ambush", 10, 0, 0.5, 0, {stunPlusPlus});

        // Assassin skill3
        EffectHealthRegen* healthRegenPlusPlus = dynamic_cast<EffectHealthRegen*>(Effect::createEffect("health regen"));
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
        EffectHealthRegen* healthRegen = dynamic_cast<EffectHealthRegen*>(Effect::createEffect("health regen"));
        EffectHealthRegen* healthRegenPlus = dynamic_cast<EffectHealthRegen*>(Effect::createEffect("health regen"));
        healthRegenPlus->setHealAmount(healthRegenPlus->getHealAmount() * 1.5);
        EffectManaRegen* manaRegenPlus = dynamic_cast<EffectManaRegen*>(Effect::createEffect("mana regen"));
        manaRegenPlus->setManaAmount(manaRegenPlus->getManaAmount() * 1.5);
        EffectManaRegen* manaRegenPlusPlus = dynamic_cast<EffectManaRegen*>(Effect::createEffect("mana regen"));
        manaRegenPlusPlus->setManaAmount(manaRegenPlusPlus->getManaAmount() * 2);

        Skill* n1_1 = new Skill("Soul Feast", 10, 0, 0.5, 0, {healthRegen});
        Skill* n1_2 = new Skill("Ghoul's Renewal", 10, 0, 0.5, 0, {healthRegenPlus, manaRegenPlus});
        Skill* n1_3 = new Skill("Necrotic Wellspring", 10, 0, 0.5, 0, {manaRegenPlusPlus});

        // Necromancer skill2
        EffectPoison* poisonPlusPlus = dynamic_cast<EffectPoison*>(Effect::createEffect("poison"));
        poisonPlusPlus->setDamage(poisonPlusPlus->getDamage() * 2);

        Skill* n2_1 = new Skill("Plague Surge", 10, 0, 0.5, 0, {poisonPlusPlus});

        // Necromancer skill3
        EffectTurn* stunPlusPlus = dynamic_cast<EffectTurn*>(Effect::createEffect("stun"));
        stunPlusPlus->setChance(stunPlusPlus->getChance() * 2);

        Skill* n3_1 = new Skill("Soul Paralysis", 10, 0, 0.5, 0, {stunPlusPlus});
    
        root1 = new SkillNode(n1_1);
        root1->setLeftNode(new SkillNode(n1_2));
        root1->setRightNode(new SkillNode(n1_3));

        root2 = new SkillNode(n2_1);

        root3 = new SkillNode(n3_1);
    }

    else if (char_type == "Berserk") {
        // Berserk skill1
        EffectDamage* critical = dynamic_cast<EffectDamage*>(Effect::createEffect("critical"));
        EffectDamage* criticalPlusPlus = dynamic_cast<EffectDamage*>(Effect::createEffect("critical"));
        criticalPlusPlus->setDamage(criticalPlusPlus->getDamage() * 2);
        EffectDamage* criticalPlus = dynamic_cast<EffectDamage*>(Effect::createEffect("critical"));
        criticalPlus->setDamage(criticalPlus->getDamage() * 1.5);
        EffectTurn* disable = dynamic_cast<EffectTurn*>(Effect::createEffect("disable"));

        Skill* b1_1 = new Skill("Fury Strike", 10, 0, 0.5, 0, {critical});
        Skill* b1_2 = new Skill("Bloodthirst Awakening", 10, 0, 0.5, 0, {criticalPlusPlus});
        Skill* b1_3 = new Skill("Crippling Rampage", 10, 0, 0.5, 0, {criticalPlus, disable});

        // Berserk skill2
        EffectDefensive* damageReductionPlusPlus = dynamic_cast<EffectDefensive*>(Effect::createEffect("damage reduction"));
        damageReductionPlusPlus->setDefense(damageReductionPlusPlus->getDefense() * 2);

        Skill* b2_1 = new Skill("Indomitable Fury", 10, 0, 0.5, 0, {damageReductionPlusPlus});

        // Berserk skill3
        EffectHealthRegen* healthRegenPlusPlus = dynamic_cast<EffectHealthRegen*>(Effect::createEffect("health regen"));
        healthRegenPlusPlus->setHealAmount(healthRegenPlusPlus->getHealAmount() * 2);

        Skill* b3_1 = new Skill("Blood Renewal", 10, 0, 0.5, 0, {healthRegenPlusPlus});

        root1 = new SkillNode(b1_1);
        root1->setLeftNode(new SkillNode(b1_2));
        root1->setRightNode(new SkillNode(b1_3));

        root2 = new SkillNode(b2_1);

        root3 = new SkillNode(b3_1);
    }
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