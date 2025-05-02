```mermaid
classDiagram
     class Stats {
        #strength : int
        #agility : int
        #intelligence : int
        +Stats(int strength, int agility, int intelligence)
        +~Stats()
        +getStrength() int
        +getAgility() int
        +getIntelligence() int
        +setStrength(int strength) void
        +setAgility(int agility) void
        +setIntelligence(int intelligence) void
    }


    class Unit {
        #name : string
        #currentHealth : int
        #maxHealth : int
        #healthRegen : int
        #currentMana : int
        #maxMana : int
        #manaRegen : int
        #attackDamage : int
        #level : int
        #stats : Stats
        #skills : vector~Skill*~
        #activeEffects : vector~Effect*~
        +Unit(string name, int strength, int agility, int intelligence, int level)
        +virtual ~Unit()
        +getName() string
        +getCurrentHealth() int
        +getMaxHealth() int
        +getHealthRegen() int
        +getCurrentMana() int
        +getMaxMana() int
        +getManaRegen() int
        +getAttackDamage() int
        +getLevel() int
        +getTurnEffectStatus(string turnEffectName) bool
        +getSkills() vector~Skill*~
        +getActiveEffects() vector~Effect*~
        +getCombinedEffect(const vector~Effect*~& activeEffects) vector~Effect*~
        +getStats() Stats
        +setName(string name) void
        +setCurrentHealth(int currentHealth) void
        +setMaxHealth(int maxHealth) void
        +setHealthRegen(int healthRegen) void
        +setCurrentMana(int currentMana) void
        +setMaxMana(int maxMana) void
        +setManaRegen(int manaRegen) void
        +setAttackDamage(int attackDamage) void
        +setLevel(int level) void
        +setStats(int strength, int agility, int intelligence) void
        +attack(Unit& target, Inventory& inventory) void
        +takeDamage(int damage) void
        +heal(int amount) void
        +restoreMana(int amount) void
        +useSkill(Skill* skill, Unit& target) void
        +addSkill(Skill* skill) void
        +removeSkill(Skill* skill) void
        +addActiveEffect(Effect* effect) void
        +removeActiveEffect(Effect* effect) void
        +applyActiveEffect() void
        +reset() void
        #getLevelFactor(Unit& target) int
        #calculateDamage(Unit& target, int baseDamage, Inventory& inventory) int
        #updateBasicAttributes() void
    }

    class Mobs {
        +String type
        +roam()
    }

    class Character {
        #exp : int
        #gold : int
        #masteryCost : int
        #type : string
        #skillTree : SkillTree
        +Character(string name, int strength, int agility, int intelligence, int level, int exp, int gold, int masteryCost, string type)
        +virtual ~Character()
        +getExp() const: int
        +
    }

    Unit *-- Stats   
    Unit <|-- Mobs     
    Unit <|-- Character