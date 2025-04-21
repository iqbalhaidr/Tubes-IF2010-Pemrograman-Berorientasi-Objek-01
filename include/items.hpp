#ifndef ITEMS_HPP
#define ITEMS_HPP

#include "item.hpp"
#include <map>
#include <string>
#include <vector>

class Items {
private:
    std::map<std::string, Item*> itemMap;

public:
    Items(const std::string& directory);
    ~Items();

    void addItem(const std::string& id, Item* item);
    bool lookup(const std::string& id) const;
    bool lookUpbyName(const std::string& Name) const;

    Item* getItem(const std::string& id) const;
    Item* getItembyName(const std::string& Name);
    std::map<std::string, Item*> getItemMap() const { return itemMap; }

    void save(const std::string& directory) const;

    static bool isValidItemType(const std::string& type);
    static bool isValidItemRarity(const std::string& rarity);
};

#endif
