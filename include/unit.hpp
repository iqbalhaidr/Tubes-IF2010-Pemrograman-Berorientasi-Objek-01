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
        bool isStun;
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
        bool getIsStun() const { return isStun; }
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
        void setIsStun(bool isStun);
        void setStats(int strength, int agility, int intelligence);


        // Fungsi
        virtual void attack(Unit& target);
        virtual void takeDamage(int damage);
        virtual void heal(int amount);
        virtual void restoreMana(int amount);
        virtual void useSkill(string skill, Unit& target); // TEMPORARY
        virtual void addSkill(string skill); // TEMPORARY
        virtual void removeSkill(string skill); // TEMPORARY
        void addEffect(string effect); // TEMPORARY
        void removeEffect(string effect); // TEMPORARY
        void applyEffect();
        virtual void reset() = 0;



};

#endif