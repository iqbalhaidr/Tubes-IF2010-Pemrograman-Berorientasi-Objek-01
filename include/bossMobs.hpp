#ifndef BOSSMOBS_HPP
#define BOSSMOBS_HPP

#include "mobs.hpp"
#include <string>
using namespace std;

class BossMobs : public Mobs {
    protected:
        bool rageUsed;
    public:
        // ctor dtor
        BossMobs(string name, int level, int strength, int agility, int intelligence, int expReward, Mobloot& mobLoots);
        virtual ~BossMobs();
        bool isRageUsed() const;
        void rage();
        bool isBoss() override;
        void reset();


};

#endif