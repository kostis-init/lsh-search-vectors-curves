#include <iostream>
#include "random.h"

int main(){

    auto random = new Random(50);
    for (int i = 0; i < 10; ++i) {
        std::cout << random->getRandomNumber() << std::endl;
    }

    return 0;
}