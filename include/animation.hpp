#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
#include <string>
#include <algorithm> 

class Animation {
public:
    void clearScreen();
    std::vector<std::string> getAnimationFrames();
    std::vector<std::string> shop();
    void animate(const std::vector<std::string>& frames, int delayMs = 300, int repeat = 5);
    void animateWalkingToShop(const std::vector<std::string>& shop, int animationSpeed = 150, int totalFrames = 25);
};

#endif // ANIMATION_HPP