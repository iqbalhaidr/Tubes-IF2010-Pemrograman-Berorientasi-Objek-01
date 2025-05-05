#include "../include/orc.hpp"

Orc::Orc(int level, int expReward, Mobloot& mobLoots)
    : BasicMobs("Orc", level, 15 + (level - 1) * 2, 8 + (level - 1) * 0.8,
                6 + (level - 1) * 0.5, expReward, mobLoots) {
    updateBasicAttributes();
    vector<Effect*> effects;
    string stunEffectDescription =
        "berpeluang 0.5 untuk memberikan stun selama 1 turn";
    EffectTurn* stunEffect = new EffectTurn("Brutal Strike (Stun)",
                                            stunEffectDescription, 1, 1, 50, true);
    effects.push_back(stunEffect);
    cout << "attackDamek: " << getAttackDamage() << endl;
    Skill* skill =
        new Skill("Brutal Strike", 14, 0, 15, attackDamage * 1.5, effects);
    addSkill(skill);
}

Orc::~Orc() {}

void Orc::updateBasicAttributes() {
    setAttackDamage(4 * getStats().getStrength());
}