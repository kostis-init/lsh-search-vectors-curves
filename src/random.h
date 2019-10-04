#ifndef ALGORITHMS_PROJECT_RANDOM_H
#define ALGORITHMS_PROJECT_RANDOM_H

#include <random>

class Random {

private:

    std::default_random_engine engine;
    int max;

public:

    Random(int max);
    int getRandomNumber();

};

#endif //ALGORITHMS_PROJECT_RANDOM_H
