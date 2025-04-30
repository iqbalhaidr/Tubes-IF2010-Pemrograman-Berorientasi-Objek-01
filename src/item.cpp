#include "../include/item.hpp"

Item::Item(std::string ItemId, std::string Name, std::string type, std::string rarity, double baseStat, const std::vector<Effect*>& Effects){
    this->itemId = itemId;
    this->name = Name;
    this->type = type;
    this->rarity = rarity;
    this->baseStat = baseStat;
    for(size_t i =0; i< Effects.size(); i++){
        effects.push_back(Effects[i]->clone());
    }
}

Item::Item(const Item& other){
    this->name = other.name;
    this->type = other.type;
    this->rarity = other.rarity;
    this->baseStat = other.baseStat;
    const auto& otherEffects = other.getEffects();
    for (const auto* effect : otherEffects) {
        effects.push_back(effect->clone());
    }
}

Item::~Item() {
    for(size_t i =0; i< effects.size(); i++){
        delete effects[i];
    }
}

bool Item::operator==(const Item& other){
    return other.itemId == this->itemId && other.name == this->name;
}

std::string Item::getName() const{
    return name;
}

std::string Item::getItemType() const{
    return type;
}

std::string Item::getRarity() const{
    return rarity;
}


double Item::getBaseStat() const{
    return baseStat;
}

std::vector<Effect*> Item::getEffects() const {
    return effects;
}

double Item :: getStatMultiplier() const {
    if (rarity == "E") return 1.0;
    if (rarity == "D") return 1.2;
    if (rarity == "C") return 1.5;
    if (rarity == "B") return 2.0;
    if (rarity == "A") return 3.0;
    if (rarity == "S") return 6.0;
    return 1.0; 
}

Item* Item::cloneItem(){
    return new Item(*this);
}

double Item :: getFinalStat() const {
    return baseStat * getStatMultiplier(); 
}

void Item::scaleItemEffect(){
    double multiplier = Item::getStatMultiplier();
    for(Effect* e : effects){
        if (dynamic_cast<EffectTurn*>(e)){
            double time = multiplier * e->getDuration();
            e->setDuration(time + e->getDuration());
        }
        else if(auto regen = dynamic_cast<EffectHealthRegen*>(e)){
            double healAmount  = multiplier * regen->getHealAmount();
            regen ->setHealAmount(healAmount + regen->getHealAmount());
            double time = multiplier*regen->getDuration();
            regen->setDuration(time + regen->getDuration());
        }
        else if (auto mana = dynamic_cast<EffectManaRegen*>(e)){
            double manaAmount  = multiplier * mana->getManaAmount();
            mana->setManaAmount(manaAmount + mana->getManaAmount());
            double time = multiplier*mana->getDuration();
            mana->setDuration(time + mana->getDuration());
        }
        else if (auto turnBased = dynamic_cast<EffectPoison*>(e)){
            double time = multiplier*turnBased->getDuration();
            double dmg = multiplier * turnBased->getDamage();
            turnBased->setDuration(time + turnBased->getDuration());
            turnBased->setDamage(dmg + turnBased->getDamage());
        }
        else if (auto damageEfect = dynamic_cast<EffectDamage*>(e)){
            double damage = multiplier * damageEfect->getDamage();
            double c = multiplier * damageEfect->getChance();
            damageEfect->setChance(c + damageEfect->getChance());
            damageEfect->setDamage(damage + damageEfect->getDamage());
        }
        else if (auto defensiveEffect = dynamic_cast<EffectDefensive*>(e)){
            double def = multiplier * defensiveEffect->getDefense();
            double c = multiplier * defensiveEffect->getChance();
            defensiveEffect->setChance(c + defensiveEffect->getChance());
            defensiveEffect->setDefense(def + defensiveEffect->getDefense());
        }
        
    }
}


