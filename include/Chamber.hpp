#ifndef CHAMBER_H
#define CHAMBER_H

#define BASE_STATS 100;

// #include "Char.hpp"

class Chamber {
   private:
    int rewardExp;
    int rewardGold;
    int difficultyScaling;

   public:
    // 4 Sekawan
    Chamber();
    Chamber(int rewardExp, int rewardGold, int difficultyScaling);
    Chamber(const Chamber&);
    ~Chamber();
    Chamber& operator=(const Chamber&);

    // Getter
    int getRewardExp();
    int getRewardGold();
    int getDifficultyScaling();

    // Setter
    void setRewardExp(int);
    void setRewardGold(int);
    void setDifficultyScaling(int);

    // Pure virtual function
    // virtual bool battle(Char&, Prize&) = 0;
};

#endif