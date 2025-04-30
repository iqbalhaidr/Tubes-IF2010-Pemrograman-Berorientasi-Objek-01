#ifndef ITEMS_HPP
#define ITEMS_HPP

#include "item.hpp"
#include <map>
#include <string>
#include <vector>
#include "EffectInclude.hpp"

class Items {
    private:
        std::map<std::string, Item*> itemMap;
    
    public:
        static bool isValidItemType(const std::string& type);
        static bool isValidItemRarity(const std::string& rarity);
        static Items createFromDirectory(const std::string& directory) ;
    
        Items(const std::map<std::string, Item*> itemMap);
        ~Items();
    
        void addItem(const std::string& id, Item* item);
        bool lookup(const std::string& id) const;
        bool lookUpbyName(const std::string& Name) const;

    
        Item* getItem(const std::string& id) const;
        Item* getItembyName(const std::string& Name);
        std::map<std::string, Item*> getItemMap() const { return itemMap; }
    
        void save(const std::string& directory) const;
    
    
    };

#endif
