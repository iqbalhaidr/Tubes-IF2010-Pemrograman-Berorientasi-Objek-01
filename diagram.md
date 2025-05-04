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
        +Assassin(string name,  int strength = 16, int agility = 24, int intelligence = 19, int level = BASE_LEVEL, int exp = BASE_EXP, int gold = BASE_GOLD, int masteryCost = BASE_MASTERY_COST, vector<string> skillNames)
        +~Assassin()
        +getCriticalChance() float
        +getCriticalMultiplier() int
        +setCriticalChance(float criticalChance) void
        +setCriticalMultiplier(int criticalMultiplier) void
        +attack(Unit& target, Inventory& inventory) void
        +takeDamage(int damage, Inventory& inventory) void
        +levelUp() void

        

    }

    class Armor {
        -durability : double
        +Armor(string itemID, string name, string type, string rarity, double baseStat, vector<Effect*>& effects)
        +Armor(const Armor& other)
        +~Armor()
        +isConsumable() bool
        +isStackable() bool
        +cloneItem() Item*
    }



    class BasicMobs{
        +BasicMobs(string name, int level, int strength, int agility, int intelligence, int expReward, Moobloot& mobLoots)
    }

    class Character {
        <<abstract>>
    }

    class Berserker {
        -rageMultiplier : int
        -updateBasicAttributes() void
        +Berserker(string name, int strength = 28, int agility = 17, int intelligence = 14, int level = BASE_LEVEL, int exp = BASE_EXP, int gold = BASE_GOLD, int masteryCost = BASE_MASTERY_COST, vector<string> skillNames)
        +~Berserker()
        +getRageMultiplier() int
        +setRageMultiplier(int rageMultiplier) void
        +attack(Unit& target, Inventory& inventory) void
        +useSkill(Skill* skill, Unit& target, Inventory& inventory) void
        +levelUp() void
    }
    
class Chamber {
    -rewardExp : int
    -rewardGold : int
    -enemyCount : int
    -enemies : vector<Mobs*>
    -isLastChamber : bool
    -minMobLevel : int
    -maxMobLevel : int
    -mobLoots : Mobloot*

    +Chamber(bool isLast, int minMobLevel, int maxMobLevel, Mobloot& mobLoots)
    +Chamber(const Chamber&)
    +~Chamber()
    +operator=(const Chamber&)

    +getRewardExp() int
    +getRewardGold() int
    +getEnemyCount() int
    +isLast() int
    +getMinMobLevel() int
    +getMaxMobLevel() int
    +getEnemies() vector<Mobs*>

    +generateRewardGold() int
    +generateRewardExp() int
    +generateEnemyCount() int
    +generateBasicMobs(int level) BasicMobs*
    +generateBossMobs(int level) BossMobs*
    +generateEnemies() void
    +battle(Character&, Inventory&, Reward&, Items&) bool
    +displayInfo() void
    +inputOption() int
    +removeExpiredEffects(Unit*) void
    +inputSkillOption(Unit*) int
    +useItemOption(Character&, Inventory&, Items&, Unit&) void
    +useItemMenu(Character&, Inventory&, Items&, Unit&) bool
    +unequipMenu(Character&, Unit&, Inventory&) void
    +displayPlayerStatus(Character&) void
    +displayEnemyStatus(Mobs*) void
}

class Characters {
    -characterMap : map<string, Character*>

    +Characters(const string& directory)
    +~Characters()
    +addCharacters(Character* Character) void
    +searchCharacter(const string& name) const bool
    +getCharacterbyName(const string& Name) Character*
    +getCharacterMap() const map<string, Character*>
    +displayAvailableCharacters() void
    +save(const string& directory) const void
}



class DarkKnight {
    +DarkKnight(int level, int expReward, Mobloot& mobLoots)
    +~DarkKnight()
    +updateBasicAttributes() void
}

class Dungeon {
    -totalChambers : int
    -chambers : vector<Chamber*>
    -rewardExp : int
    -rewardGold : int
    -bonusItem : Item*
    -isDD : bool
    -prize : Reward
    -penaltyExp : int
    -penaltyGold : int
    -rank : string
    -minLevel : int
    -entryCost : int

    +Dungeon(string rank, Mobloot &mobLoots, Items &items, Character &c)
    +~Dungeon()
    +start(Character&, Inventory&, Items&) void
    +randomizeDoubleDungeon() void
    +helperSet(Items&, Character&) void
    +generateChambers(Mobloot&) void
    +displayInfo() void
    +substractExp(Character*, int) void
    +substractGold(Character*, int) void
    +typeEffect(const string&, int delayMs = 50) void
    +welcomeMessage() void
    +winningMessage() void
    +losingMessage() void
}

class Effect {
        #name: string
        #description: string
        #duration: double
        -remainingDuration: double
        +Effect(string, string, double, double)
        +~Effect()
        +Effect(Effect&)
        +operator=(Effect&) Effect&
        +createEffect(string) Effect*
        +operator==(Effect&) bool
        +getName() string
        +getDescription() string
        +getDuration() double
        +getRemainingDuration() double
        +setName(string) void
        +setDescription(string) void
        +setDuration(double) void
        +setRemainingDuration(double) void
        +apply(Unit*) double
        +remove(Unit*) void
        +clone() Effect* 
        +isDamage() bool
        +isDefensive() bool
        +isTurnBased() bool
        +isTurn() bool
        +isHealthRegen() bool
        +isManaRegen() bool
        +isThrowable() bool
        +isPoison() bool
        +isHealth() bool
        +isManaReduc() bool
        +isReducePower() bool
        +decreaseRemainingDuration() void
    }

    class EffectDamage {
        -chance : int
        -damage : double
        +EffectDamage(string, string, double, double, int, double)
        +~EffectDamage()
        +EffectDamage(EffectDamage&)
        +operator=(EffectDamage&) EffectDamage&
        +getChance() double
        +getDamage() double
        +setChance(double) void
        +setDamage(double) void
        +apply(Unit*) double
        +remove(Unit*) void
        +clone() Effect* 
        +isDamage() bool
    }

    class EffectDefensive {
        -chance : int
        -defense : double
        +EffectDefensive(string, string, double, double, int, double, double)
        +~EffectDefensive()
        +EffectDefensive(EffectDefensive&)
        +operator=(EffectDefensive&) EffectDefensive&
        +getChance() double const
        +getDefense() double const
        +setChance(double) void
        +setDefense(double) void
        +apply(Unit*) double
        +remove(Unit*) void
        +clone() Effect* 
        +isDefensive() bool
    }

    class EffectHealth {
        -healAmount : int
        -chance : double
        -baseHealAmount : int
        +EffectHealth(string, string, double, double, double, int)
        +~EffectHealth()
        +EffectHealth(EffectHealth&)
        +operator=(EffectHealth&) EffectHealth&
        +getHealAmount() int
        +setHealAmount(int) void
        +getChance() double
        +setChance(double) void
        +apply(Unit*) double
        +remove(Unit*) void
        +clone() Effect* 
        +isHealth() bool
    }

    class EffectHealthRegen {
        -healAmount : int
        +EffectHealthRegen(string, string, double, double, int)
        +~EffectHealthRegen()
        +EffectHealthRegen(EffectHealthRegen&)
        +operator=(EffectHealthRegen&) EffectHealthRegen&
        +getHealAmount() int
        +setHealAmount(int) void
        +apply(Unit*) double
        +remove(Unit*) void
        +clone() Effect*
        +isHealthRegen() bool
    }


  class EffectManaReduc {
        -manaAmount : double
        +EffectManaReduc(string, string, double, double, double)
        +~EffectManaReduc()
        +EffectManaReduc(EffectManaReduc&)
        +operator=(EffectManaReduc&) EffectManaReduc&
        +getManaAmount() double const
        +setManaAmount(int) void
        +apply(Unit*) double
        +remove(Unit*) void
        +isManaReduc() bool
    }


     class EffectManaRegen {
        -manaAmount : int
        +EffectManaRegen(string name, string desc, double duration, double remain_dur, int manaAmount)
        +~EffectManaRegen()
        +EffectManaRegen(EffectManaRegen& other)
        +operator=(EffectManaRegen& other) EffectManaRegen&
        +getManaAmount() int
        +setManaAmount(int mA) void
        +apply(Unit* unit) double
        +remove(Unit* unit) void
        +clone() Effect*
        +isManaRegen() bool
    }


class EffectPoison {
        -damage : double
        -chance : double
        +EffectPoison(string name, string description, double duration, double remainingDuration, double chance, double damage)
        +~EffectPoison()
        +EffectPoison(EffectPoison& other)
        +operator=(EffectPoison& other) EffectPoison&
        +getDamage() double
        +setDamage(int damage) void
        +getChance() double const
        +setChance(int chance) void
        +apply(Unit* unit) double
        +clone() Effect* const
        +remove(Unit* unit) void
        +isThrowable() bool
        +isPoison() bool
    }

     class EffectTurn {
        -chance : int
        +EffectTurn(string name, string description, double duration, double remainingDuration, int chance)
        +~EffectTurn()
        +EffectTurn(EffectTurn& other)
        +operator=(EffectTurn& other) EffectTurn&
        +getChance() int const
        +setChance(int chance) void
        +apply(Unit* unit) double
        +clone() Effect* const
        +isTurn() bool
    }


class EffectTurnBasedBased {
        +EffectTurnBasedBased(string name, string description, double duration, double remainingDuration)
        +~EffectTurnBasedBased()
        +EffectTurnBasedBased(EffectTurnBasedBased& other)
        +operator=(EffectTurnBasedBased& other) EffectTurnBasedBased&
        +isTurnBased() bool
        +clone() Effect* const
        +apply(Unit* unit) double
        +remove(Unit* unit) void
    }


class Player {
        -itemMap : Items*
        -inv : Inventory*
        -playerChar : Character*
        +Player(string dir, string charType, Items& itemMap, Characters& allChar, int type)
        +~Player()
        +goToDungeon(Mobloot& moobLoot, Items& itemMap) void
        +goToShop(Shop& shop) void
        +buyFromShop(Shop& shop, string itemId, int quantity) void
        +sellToShop(Shop& shop, string itemId, int quantity) void
        +showInventory(bool isBackpack) void
        +showCurrency() void
        +reduceItemInvetory(string addAbleItem, int target) void
        +getChar() Character*
        +getInv() Inventory*
    }





    class InputOutputException {
        -errorMessage string
        +InputOutputException() 
        +InputOutputException(string message)
        +what() char const*
    }

    class InventoryEror {
        -errorMessage string
        +InventoryEror()
        +InventoryEror(string message)
        +what() char const*
    }

    class InventoryFull {
        -errorMessage string
        -overflow int
        +InventoryFull()
        +InventoryFull(string message, int total)
        +getOverflow() int const
        +what() char const*
    }

    class CharactersError {
        -errorMessage string
        +CharactersError()
        +CharactersError(string message)
        +what() char const*
    }

    class ItemNotFound {
        -errorMessage string
        +ItemNotFound()
        +ItemNotFound(string message)
        +what() char const*
    }

    class InvalidCommand {
        -errorMessage string
        +InvalidCommand()
        +InvalidCommand(string message)
        +what() char const*
    }

    class StockError {
        -errorMessage string
        +StockError()
        +StockError(string message)
        +what() char const*
    }

    class GoldNotEnough {
        -errorMessage string
        +GoldNotEnough()
        +GoldNotEnough(string message)
        +what() char const*
    }

    class ManaNotEnough {
        -errorMessage string
        +ManaNotEnough()
        +ManaNotEnough(string message)
        +what() char const*
    }

    class MasteryCostNotEnough {
        -errorMessage string
        +MasteryCostNotEnough()
        +MasteryCostNotEnough(string message)
        +what() char const*
    }

    class InvalidValue {
        -errorMessage string
        +InvalidValue()
        +InvalidValue(string message)
        +what() char const*
    }

    class InvalidSkill {
        -errorMessage string
        +InvalidSkill()
        +InvalidSkill(string message)
        +what() char const*
    }


classDiagram
    class Inventory {
        -backpack : Matrix<pair<Item*, int>>
        -equipped : map<string, Item*>
        
        +Inventory(Matrix<pair<Item*, int>> backp, map<string, Item*> equippedItem)
        +centerText(string text, int width) string static
        +loadInventory(string directory, Items itemMap) Inventory static
        +saveInventory(string directory) void
        +addItem(pair<Item*, int> value) void
        +reduceItem(Item* item, int amount) void
        +handleNonConsumable(Item* item, Character& orang, Unit& target) void
        +handleConsumable(Item* item, Character& orang, Unit& target) void
        +useItem(string itemID, Character& orang, Items itemMap, Unit& target) void
        +unequipItem(Character& orang, string slot, Unit& target) void
        +equipItem(string slot, Character& orang, Item* item, Unit& target) void
        +getIdxItembyId(string itemId) pair<int, int> const
        +getBackpack() Matrix<pair<Item*, int>>
        +getEquippedItem(string slot) Item*
        +getItemById(string itemId) pair<Item*, int>
        +getItemBackpackByName(string itemName) pair<Item*, int>
        +getEquippedItemId(string slot) string const
        +setEquipped(string slot, Item* item) void
        +displayBackpack() void
        +displayEquipment() void
        +getItemQtyInInvent(string itemName) int
        +displayBackpackDetails() void
    }

    Inventory --|> Character
    Inventory --|> Item
    Inventory --|> Unit
    Inventory *-- Item


    InputOutputException --|> std::exception
    InventoryEror --|> std::exception
    InventoryFull --|> std::exception
    CharactersError --|> std::exception
    ItemNotFound --|> std::exception
    InvalidCommand --|> std::exception
    StockError --|> std::exception
    GoldNotEnough --|> std::exception
    ManaNotEnough --|> std::exception
    MasteryCostNotEnough --|> std::exception
    InvalidValue --|> std::exception
    InvalidSkill --|> std::exception

    Player --> Items
    Player --> Inventory
    Player --> Characters
    Player --> Shop
    Player --> Mobloot
    Player *-- Items
    Player *-- Inventory
    Player *-- Character


    EffectTurnBasedBased --> Unit


    Effect <|-- EffectTurn
    EffectTurn --> Unit

    EffectTurnBasedBased <|-- EffectPoison
    EffectPoison --> Unit

    Effect <|-- EffectTurnBasedBased

    EffectTurnBasedBased <|-- EffectManaRegen
    EffectManaRegen --> Unit

    EffectTurnBasedBased <|-- EffectManaReduc
    EffectManaReduc --> Unit

    EffectTurnBasedBased <|-- EffectHealthRegen
    EffectHealthRegen --> Unit


    Effect <|-- EffectHealth
    EffectHealth --> Unit

    Effect <|-- EffectDefensive
    EffectDefensive --> Unit




    Effect <|-- EffectDamage
    EffectDamage --> Unit
    Dungeon *-- Chamber
    Dungeon *-- Item
    Dungeon *-- Reward
    BossMobs <|-- DarkKnight
    Chamber *-- Mobloot
    Chamber *-- Mobs
    Unit *-- Stats   
    Unit <|-- Mobs     
    Unit <|-- Character
    Character <|-- Assassin
    Item <|-- Armor
    Mobs <|-- BasicMobs
    Character <|-- Berseker
    Unit <-- Character
    Character *-- SkillTree
    Characters *-- Character


