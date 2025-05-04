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
        #isChar : bool
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
        #expReward : int
        #LootDrop : vector<pair<Item*, double>>
        +Mobs(string name, int level, int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots)
        +virtual~Mobs()
        +getExpReward() int
        +setExpReward(int expReward) void
        +reset() void

    }

    class Character {
        #exp : int
        #gold : int
        #masteryCost : int
        #type : string
        #skillTree : SkillTree
        #loadCharacterSkills(vector<string> skillNames) void
        +Character(string name, int strength, int agility, int intelligence, int level, int exp, int gold, int masteryCost, string type)
        +virtual ~Character()
        +getExp() int
        +getGold() int
        +getMasteryCost() int
        +getSkillTree() SkillTree
        +getType() string
        +setLevel(int level) void
        +setExp(int exp) void
        +setGold(int gold) void
        +setMasteryCost(int masteryCost) void
        +setType(string type) void
        +displayAvailableSkillUpgrades() void
        +UpgradeSkill(string& name) void
        +displayCharacter() void
        +virtual void levelUp() void [=0]
    }

    class Assassin {
        -criticalChance : float
        -criticalMultiplier : int
        -updateBasicAttributes() void
        +Assassin(string name,  int strength = 16, int agility = 24, int intelligence = 19, int level = BASE_LEVEL, int exp = BASE_EXP, int gold = BASE_GOLD, int masteryCost = BASE_MASTERY_COST, vector<string> skillNames = {})
        +~Assassin()
        +getCriticalChance() float
        +getCriticalMultiplier() int
        +setCriticalChance(float criticalChance) void
        +setCriticalMultiplier(int criticalMultiplier) void
        +attack(Unit& target, Inventory& inventory) void
        +takeDamage(int damage, Inventory& inventory) void
        +levelUp() void

        

    }



    Unit *-- Stats   
    Unit <|-- Mobs     
    Unit <|-- Character
    Character <|-- Assassin