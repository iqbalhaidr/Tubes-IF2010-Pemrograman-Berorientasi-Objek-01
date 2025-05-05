#ifndef UNIT_HPP
#define UNIT_HPP


#include "stats.hpp"
#include "skill.hpp"
#include "effect.hpp"
#include "EffectHealthRegen.hpp" 
#include "EffectManaRegen.hpp"
#include "EffectDamage.hpp"
#include "EffectDefensive.hpp"
#include "EffectPoison.hpp"
#include "EffectTurn.hpp"
#include "EffectHealth.hpp" 
#include "EffectManaReduc.hpp"
#include "EffectTurnBased.hpp"
#include "exception.hpp"

#include "inventory.hpp"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Unit {
    protected:
        string name;
        int currentHealth;
        int maxHealth;
        int healthRegen;
        int currentMana;
        int maxMana;
        int manaRegen;
        int attackDamage;
        int level;
        bool isChar;
        Stats stats;
        vector<Skill*> skills;
        vector<Effect*> activeEffects;
        int getLevelFactor(Unit& target) const;
        int calculateDamage(Unit& target, int baseDamage, Inventory& inventory); 
        virtual void updateBasicAttributes();
    public:
        // ctor dtor
        Unit(string name, int strength, int agility, int intelligence, int level);
        virtual ~Unit();

        // setter getter
        string getName() const;
        int getCurrentHealth() const;
        int getMaxHealth() const;
        int getHealthRegen() const;
        int getCurrentMana() const;
        int getMaxMana() const;
        int getManaRegen() const;
        int getAttackDamage() const;
        int getLevel() const;
        bool getTurnEffectStatus(string turnEffectName) const;
        vector<Skill*> getSkills() const; 
        vector<Effect*> getActiveEffects() const; 
        vector<Effect*> getCombinedEffect(const vector<Effect*>& activeEffects) const;

        Stats getStats() const;
        void setName(string name);
        void setCurrentHealth(int currentHealth);
        void setMaxHealth(int maxHealth);
        void setHealthRegen(int healthRegen);
        void setCurrentMana(int currentMana);
        void setMaxMana(int maxMana);
        void setManaRegen(int manaRegen);
        void setAttackDamage(int attackDamage);
        void setLevel(int level);
        void setStats(int strength, int agility, int intelligence);

        // Fungsi
        virtual void attack(Unit& target, Inventory& inventory); 
        virtual void takeDamage(int damage, Inventory& inventory);
        virtual void heal(int amount);
        virtual void restoreMana(int amount);
        virtual void useSkill(Skill* skill, Unit& target, Inventory& inventory); 
        virtual void addSkill(Skill* skill); 
        virtual void removeSkill(Skill* skill); 
        void addActiveEffect(Effect* effect); 
        void removeActiveEffect(Effect* effect); 
        void applyActiveEffect();
        virtual void reset() = 0;



};

#endif