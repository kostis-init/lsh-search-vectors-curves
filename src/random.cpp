#include <iostream>
#include <random>
#include "random.h"

Random::Random(int max){
    this->max = max;
    engine.seed(time(nullptr));
}

int Random::getRandomNumber() {
    return engine()%max + 1;
}