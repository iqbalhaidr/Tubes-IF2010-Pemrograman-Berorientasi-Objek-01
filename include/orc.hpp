#ifndef ORC_HPP
#define ORC_HPP

#include "basicMobs.hpp"
#include <string>
using namespace std;

class Orc : public BasicMobs {
    private:
        void updateBasicAttributes() override;
    public:
        // ctor dtor
        Orc(int level, int expReward, Mobloot& mobLoots);
        ~Orc();


};

#endif