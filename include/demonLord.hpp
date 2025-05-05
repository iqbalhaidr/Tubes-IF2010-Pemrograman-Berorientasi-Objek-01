#ifndef DemonLord_HPP
#define DemonLord_HPP

#include "bossMobs.hpp"
#include <string>
using namespace std;

class DemonLord : public BossMobs {
    private:
        void updateBasicAttributes() override;
    public:
        // ctor dtor
        DemonLord(int level, int expReward, Mobloot& mobLoots);
        ~DemonLord();

};

#endif