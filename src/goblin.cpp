#include "../include/goblin.hpp"

Goblin::Goblin(int level, int expReward, Mobloot& mobLoots)
 : BasicMobs("Goblin", level, 7, 15, 6, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string effectDescription = "menghilang sesaat dalam kepulan asap atau bayangan, lalu muncul tiba-tiba di belakang target untuk memberikan serangan kejutan dengan bonus critical damage, memberikan damage 2x dari attack biasa";
    EffectDamage* surpriseCritDamage = new EffectDamage("Sneaky Stab", effectDescription, 1, 1, 1, attackDamage * 2);
    effects.push_back(surpriseCritDamage);
    Skill *skill = new Skill("Sneaky Stab", 0, 0, 20, attackDamage, effects);
    addSkill(skill);
}

Goblin::~Goblin() {}

void Goblin::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getAgility());
}