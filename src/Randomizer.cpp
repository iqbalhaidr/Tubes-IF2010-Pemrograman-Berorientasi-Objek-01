#include "../include/Randomizer.hpp"

int Randomizer::random(int low, int up) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(low, up);
    return distrib(gen);
}