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
        +takeDamage(int damage, Inventory& inventory) void
        +heal(int amount) void
        +restoreMana(int amount) void
        +useSkill(Skill* skill, Unit& target, Inventory& inventory) void
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

    class BasicMobs {
        +BasicMobs(string name, int level, int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots)
        +virtual ~BasicMobs()
    }

    class BossMobs {
        -rageUsed : boolean
        +BossMobs(string name, int level, int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots)
        -virtual ~BossMobs()
        +rage() void
        +reset() void
    }

    class Slime {
        -updateBasicAttributes() void
        +Slime(int level, int expReward, Mobloot& mobLoots)
        + ~Slime()
    }

    class Skeleton {
        -updateBasicAttributes() void
        +Skeleton(int level, int expReward, Mobloot& mobLoots)
        + ~Skeleton()
    }

    class Orc {
        -updateBasicAttributes() void
        +Orc(int level, int expReward, Mobloot& mobLoots)
        + ~Orc()
    }

    class Goblin {
        -updateBasicAttributes() void
        +Goblin(int level, int expReward, Mobloot& mobLoots)
        + ~Goblin()
    }

    class Ogre {
        -updateBasicAttributes() void
        +Ogre(int level, int expReward, Mobloot& mobLoots)
        + ~Ogre()
    }

    class Lich {
        -updateBasicAttributes() void
        +Lich(int level, int expReward, Mobloot& mobLoots)
        + ~Lich()
    }

    class DemonLord {
        -updateBasicAttributes() void
        +DemonLord(int level, int expReward, Mobloot& mobLoots)
        + ~DemonLord()
    }

    class DarkKnight {
        -updateBasicAttributes() void
        +DarkKnight(int level, int expReward, Mobloot& mobLoots)
        + ~DarkKnight()
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
        +Assassin(string name,  int strength = 16, int agility = 24, int intelligence = 19, int level = BASE_LEVEL, int exp = BASE_EXP, int gold = BASE_GOLD, int masteryCost = BASE_MASTERY_COST, vector<string> skillNames)
        + ~Assassin()
        +getCriticalChance() float
        +getCriticalMultiplier() int
        +setCriticalChance(float criticalChance) void
        +setCriticalMultiplier(int criticalMultiplier) void
        +attack(Unit& target, Inventory& inventory) void
        +takeDamage(int damage, Inventory& inventory) void
        +levelUp() void
    }

    class Berserker {
        -rageMultiplier : int
        -updateBasicAttributes() void
        +Berserker(string name, int strength = 28, int agility = 17, int intelligence = 14, int level = BASE_LEVEL, int exp = BASE_EXP, int gold = BASE_GOLD, int masteryCost = BASE_MASTERY_COST, vector<string> skillNames)
        + ~Beserker()
        +getRageMultiplier() int
        +setRageMultiplier(int rageMultiplier) void
        +attack(Unit& target, Inventory& inventory) void
        +useSkill(Skill* skill, Unit& target, Inventory& inventory) void
        +levelUp() void
    }

    class Fighter {
        -blockChance : float
        -updateBasicAttributes() void
        +Fighter(string name, int strength = 27, int agility = 17, int intelligence = 15, int level = BASE_LEVEL, int exp = BASE_EXP, int gold = BASE_GOLD, int masteryCost = BASE_MASTERY_COST, vector<string> skillNames)
        + ~Fighter()
        +getBlockChance() int
        +getBlockChance(int blockChance) void
        +takeDamage(int damage, Inventory& inventory) void
        +useSkill(Skill* skill, Unit& target, Inventory& inventory) void
        +levelUp() void
    }

    class Mage {
        -extraMana : int
        -updateBasicAttributes() void
        +Mage(string name, int strength = 16, int agility = 20, int intelligence = 25, int level = BASE_LEVEL, int exp = BASE_EXP, int gold = BASE_GOLD, int masteryCost = BASE_MASTERY_COST, vector<string> skillNames)
        + ~Mage()
        +getExtraMana() int
        +setExtraMana(int extraMana) void
        +attack(Unit& target, Inventory& inventory) void
        +useSkill(Skill* skill, Unit& target, Inventory& inventory) void
        +levelUp() void
    }

    class Mage {
        -summons : boolean
        -summonChance : double
        -summonTurns : int
        -updateBasicAttributes() void
        +Necromancer(string name, int strength = 13, int agility = 16, int intelligence = 28, int level = BASE_LEVEL, int exp = BASE_EXP, int gold = BASE_GOLD, int masteryCost = BASE_MASTERY_COST, vector<string> skillNames)
        + ~Necromancer()
        +getSummonChance() double
        +setSummonChance(double criticalChance) void
        +attack(Unit& target, Inventory& inventory) void
        +useSkill(Skill* skill, Unit& target, Inventory& inventory) void
        +levelUp() void
    }

    class Characters {
        -characterMap :  map<string, Character*>
        +Characters(const string& directory)
        + ~Characters()
        +searchCharacter(const string& name) boolean
        +getCharacterbyName(const string& Name) Character*
        +getCharacterMap() map<string, Character*>
        +displayAvailableCharacters() void
        +addCharacters(Character* Character) void
        +save(const string& directory) void
    }

    class Mobloot {
        -MobLoots : map<string, vector<pair<Item*, double>>>
        +Mobloot(const string& directory, const Items& itemMap)
        + ~Mobloot()
        +getLootforMob(const string& name) vector<pair<Item*, double>>
    }


    Unit *-- Stats   
    Unit <|-- Mobs     
    Unit <|-- Character
    Mobs <|-- BasicMobs
    Mobs <|-- BossMobs
    Mobs o-- Mobloot

    BasicMobs <|-- Slime
    BasicMobs <|-- Goblin
    BasicMobs <|-- Skeleton
    BasicMobs <|-- Orc
    BossMobs <|-- Ogre
    BossMobs <|-- Lich
    BossMobs <|-- DemonLord
    BossMobs <|-- DarkKnight

    Character <|-- Assassin
    Character <|-- Berserker
    Character <|-- Fighter
    Character <|-- Mage
    Character <|-- Necromancer
    Characters o-- Character 