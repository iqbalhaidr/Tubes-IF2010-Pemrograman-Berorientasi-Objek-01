#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>

class Item {
private:
    std::string name;
    std::string type;
    std::string rarity;
    double baseStat;
    std::vector<std::string> effects;

public:
    Item(std::string name, std::string type, std::string rarity,
         double baseStat,
         const std::vector<std::string>& effects);

    ~Item();

    std::string getName() const;
    std::string getItemType() const;
    std::string getRarity() const;
    int getLevel();
    double getBaseStat() const;
    std::vector<std::string> getEffects();
    double getStatMultiplier() const;
    double getFinalStat() const;
};

#endif
