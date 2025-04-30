#include "../include/Randomizer.hpp"

int Randomizer::random(int low, int up) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(low, up);
    return distrib(gen);
}

bool Randomizer::chance(float probability) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(0.0f, 1.0f); // [0.0, 1.0)
    return distrib(gen) < probability;
}