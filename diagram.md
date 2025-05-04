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

    class Reward {
        -exp : int
        -gold : int
        -items : map<Item*, int>

        +Reward()
        +~Reward()
        +getExp() int
        +getGold() int
        +getItems() map<Item*, int>
        +addExp(int exp) void
        +addGold(int gold) void
        +addItem(Item* item, int count) void
        +displayInfo() void
        +giveTo(Character* c, Inventory* inv) void
        +giveTo(Inventory* inv) void
        +addExpToCharacter(Character* c, int exp) void
        +addGoldToCharacter(Character* c, int gold) void
    }
    Dungeon <|-- Reward

    class Randomizer {
        +random(int low, int up) int
        +chance(float probability) bool
    }

    class Potion {
        -durability : double

        +Potion(string itemId, string name, string type, string rarity, double baseStat, vector<Effect*> effects)
        +Potion(const Potion& other)
        +~Potion()
        +isConsumable() const bool
        +isStackable() const bool
        +cloneItem() Item*
    }
    Item <|-- Potion

    class Pendant {
        -durability : double

        +Pendant(string itemId, string name, string type, string rarity, double baseStat, vector<Effect*> effects)
        +Pendant(const Pendant& other)
        +~Pendant()
        +isConsumable() const bool
        +isStackable() const bool
        +cloneItem() Item*
    }
    Item <|-- Pendant

    class Shop {
        -availableItems : map<string, tuple<string, int, int>>
        -itemMap : Items*
        -shopConfig : map<string, int>
        -categoryShop : map<string, vector<pair<string, int>>>

        +Shop(const string& directory)
        +~Shop()
        +saveShop(const string& directory) void
        +buyItem(const string& itemName, int quantity) pair<Item*, int>
        +sellItem(const string& itemName, int quantity) pair<Item*, int>
        +restock() void
        +setStock(const string& itemName, int stock) void
        +getCurrentStock(const string& itemName) const int
        +getPrice(const string& itemName) const int
        +displayDetails(string itemName) const void
        +displayShop() const void
    }

    class Weapon {
        -durability : double

        +Weapon(string itemId, string name, string type, string rarity, double baseStat, vector<Effect*> effects)
        +Weapon(const Weapon& other)
        +~Weapon()
        +isConsumable() const bool
        +isStackable() const bool
        +cloneItem() Item*
    }
    Item <|-- Weapon

    class Item {
        -itemId : string
        -name : string
        -type : string
        -rarity : string
        -baseStat : double
        -effects : vector<Effect*>

        +Item(string itemId, string name, string type, string rarity, double baseStat, vector<Effect*> effects)
        +Item(const Item& other)
        +~Item()
        +operator==(other : const Item&) bool
        +getId() string
        +getName() const string
        +getItemType() const string
        +getRarity() const string
        +getBaseStat() const double
        +getEffects() const vector<Effect*>
        +getStatMultiplier() const double
        +getFinalStat() const double
        +scaleItemEffect() void
        +isConsumable() const bool
        +isStackable() const bool
        +cloneItem() Item*
    }

    class Items {
        -itemMap : map<string, Item*>

        +Items(itemMap : map<string, Item*>)
        +~Items()
        +addItem(id : string, item : Item*) void
        +lookup(id : string) const bool
        +lookUpbyName(Name : string) const bool
        +getItem(id : string) const Item*
        +getItembyName(Name : string) Item*
        +getItemMap() const map<string, Item*>
        +save(directory : string) const void
        +isValidItemType(type : string) static bool
        +isValidItemRarity(rarity : string) static bool
        +createFromDirectory(directory : string) static Items
    }

    class Matrix {
        -rows : int
        -cols : int
        -matriks : vector<vector<T>>
        -defaultVal : T

        +Matrix()
        +Matrix(r : int, c : int)
        +~Matrix()
        +setDefault(i : int, j : int) void
        +set(i : int, j : int, value : T) void
        +get(i : int, j : int) const T
        +isInMatrix(predicate : function<bool(T)>) const pair<int, int>
        +isEmptyCell(Rows : int, Cols : int) bool
        +getRows() int
        +getCols() int
    }
    Inventory *-- Matrix

    class Skill {
        -name : string
        -manaCost : double
        -masterCost : double
        -skillChance : double
        -damage : double
        -effects : vector<Effect*>

        +Skill(name : string, manaCost : double, masterCost : double, skillChance : double, damage : double, effects : vector<Effect*>)
        +~Skill()
        +Skill(other : Skill&)
        +operator=(other : Skill&) : Skill&
        +operator==(other : Skill) const : bool

        +getName() const : string
        +getManaCost() const : double
        +getMasterCost() const : double
        +getskillChance() const : double
        +getDamage() const : double
        +getEffects() const : vector<Effect*>

        +setName(name : string) : void
        +setManaCost(manaCost : double) : void
        +setMasterCost(masterCost : double) : void
        +setskillChance(skillChance : double) : void
        +setDamage(damage : double) : void
        +setEffects(effects : vector<Effect*>) : void
    }

    class SkillNode {
        -skill : Skill*
        -left : SkillNode*
        -right : SkillNode*
        +unlocked : bool

        +SkillNode(skill : Skill*)
        +SkillNode(skill : Skill*, left : SkillNode*, right : SkillNode*)
        +~SkillNode()
        +SkillNode(other : const SkillNode&)
        +operator=(other : const SkillNode&) : SkillNode&

        +getSkill() const : Skill*
        +getLeftNode() const : SkillNode*
        +getRightNode() const : SkillNode*
        +getLeftSkill() const : Skill*
        +getRightSkill() const : Skill*
        +setLeftNode(left : SkillNode*) : void
        +setRightNode(right : SkillNode*) : void
        +canRemove() const : bool
    }
    SkillNode *-- Skill 

    class SkillTree {
        -root1 : SkillNode*
        -root2 : SkillNode*
        -root3 : SkillNode*
        -char_type : string

        +currentSkills : vector<SkillNode*>

        +SkillTree(char_type : string)
        +~SkillTree()

        +destroy(root : SkillNode*) : void
        +getAvailableUpgrade(res : vector<SkillNode*>) : vector<SkillNode*>
        +upgradeSkill(skill_awal : SkillNode*, skill_baru : SkillNode*) : void
        +getParent(child : Skill) : SkillNode*
        +getRoot() : vector<SkillNode*>
        +getNodebyName(name : string, root : SkillNode*) : SkillNode*
    }
    SkillTree *-- SkillNode


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
