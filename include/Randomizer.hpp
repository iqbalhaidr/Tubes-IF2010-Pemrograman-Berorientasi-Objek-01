#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <random>

class Randomizer {
   public:
    // Return random number dalam selang [low, up]
    static int random(int low, int up);
};

#endif