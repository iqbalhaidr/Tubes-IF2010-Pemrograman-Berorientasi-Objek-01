#ifndef UNIT_HPP
#define UNIT_HPP

#define MAX_HEALTH 10000
#define MAX_MANA 2000
#define MAX_ATTACK_DAMAGE 1000
#include "stats.hpp"
#include "skill.hpp"
#include "effect.hpp"
#include "EffectHealthRegen.hpp" // diperlukan di CPP!
#include "EffectManaRegen.hpp"
#include "EffectDamage.hpp"
#include "EffectDefensive.hpp"

#include "inventory.hpp"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
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
        Stats stats;
        map<string, bool> turnActiveEffectstatus; 
        vector<Skill*> skills;
        vector<Effect*> activeEffects;
        // int getLevelFactor(Unit& target);
        int calculateDamage(Unit& target, int baseDamage, Inventory& inventory); // TEMPORARY
        virtual void updateBasicAttributes();
    public:
        // ctor dtor
        Unit::Unit(string name, int strength, int agility, int intelligence);
        ~Unit();

        // setter getter
        string getName() const;
        int getCurrentHealth() const;
        int getMaxHealth() const;
        int getHealthRegen() const;
        int getCurrentMana() const;
        int getMaxMana() const;
        int getManaRegen() const;
        int getAttackDamage() const;
        map<string, bool> getTurnActiveEffectStatus() const;
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
        void setTurnActiveEffectStatus(string turnEffect);
        void setStats(int strength, int agility, int intelligence);

        // Fungsi
        virtual void attack(Unit& target, Inventory& inventory); // TEMPORARY
        virtual void takeDamage(int damage);
        virtual void heal(int amount);
        virtual void restoreMana(int amount);
        virtual void useSkill(Skill* skill, Unit& target); // TEMPORARY
        virtual void addSkill(Skill* skill); // TEMPORARY
        virtual void removeSkill(Skill* skill); // TEMPORARY
        void addActiveEffect(Effect* effect); // TEMPORARY
        void removeActiveEffect(Effect* effect); // TEMPORARY
        void applyActiveEffect();
        virtual void reset() = 0;



};

#endif