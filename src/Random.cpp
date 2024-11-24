#include "Random.h"
#include <ctime>

std::mt19937& getRandomEngine() {
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    return rng;
}

float getRandomNumber() {
     static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
     return dist(getRandomEngine());
}
