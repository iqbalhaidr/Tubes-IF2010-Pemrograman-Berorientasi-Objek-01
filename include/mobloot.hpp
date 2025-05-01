#ifndef Mobloot_HPP
#define Mobloot_HPP

#include "items.hpp"
#include <map>
#include <string>
#include <vector>
#include <utility>
using namespace std;

class Mobloot {
private:
    map<string, vector<pair<Item*, double>>> MobLoots;

public:
    Mobloot(const string& directory, const Items& itemMap);
    ~Mobloot();
    vector<pair<Item*, double>> getLootforMob(const string& name);



};

#endif