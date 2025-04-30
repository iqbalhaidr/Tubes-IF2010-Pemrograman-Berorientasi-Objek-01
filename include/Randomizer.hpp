#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <random>

class Randomizer {
   public:
    // Return random number dalam selang [low, up]
    static int random(int low, int up);

    // Menghitung peluang, mengembalikan true jika HIT
    static bool chance(float probability);
};

#endif