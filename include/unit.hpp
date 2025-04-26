#ifndef UNIT_HPP
#define UNIT_HPP

#define MAX_HEALTH 10000
#define MAX_MANA 2000
#define MAX_ATTACK_DAMAGE 1000
#include "stats.hpp"
#include <string>
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
        vector<string> skills;
        vector<string> effects;
    public:
        // ctor dtor
        Unit(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage, int strength, int agility, int intelligence);
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
        vector<string> getSkills() const; // TEMPORARY
        vector<string> getEffects() const; // TEMPORARY

        Stats getStats() const;
        void setName(string name);
        void setCurrentHealth(int currentHealth);
        void setMaxHealth(int maxHealth);
        void setHealthRegen(int healthRegen);
        void setCurrentMana(int currentMana);
        void setMaxMana(int maxMana);
        void setManaRegen(int manaRegen);
        void setAttackDamage(int attackDamage);
        void setStats(int strength, int agility, int intelligence);

        // Fungsi
        virtual void attack(Unit& target);
        virtual void takeDamage(int damage);
        virtual void heal(int amount);
        virtual void restoreMana(int amount);
        virtual void useSkill(string skill); // TEMPORARY
        virtual void addSkill(string skill); // TEMPORARY
        virtual void removeSkill(string skill); // TEMPORARY
        virtual void addEffect(string effect); // TEMPORARY
        virtual void removeEffect(string effect); // TEMPORARY
        virtual void reset() = 0;



};

#endif