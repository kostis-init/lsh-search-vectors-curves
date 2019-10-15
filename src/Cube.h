#ifndef ALGORITHMS_PROJECT_CUBE_H
#define ALGORITHMS_PROJECT_CUBE_H

#include "LSH.h"

class Cube {
private:

    int dimension = 3;
    int max_checked = 10;
    int max_probes = 2;

    LSH* lsh;

public:

    Cube(){lsh = new LSH();}
    ~Cube(){delete lsh;}

    int getDimension() const {return dimension;}
    int getMaxChecked() const {return max_checked;}
    int getMaxProbes() const {return max_probes;}
    auto getLsh() const {return lsh;}

    void setDimension(int dimension) {
        this->dimension = dimension;
    }

    void setMaxChecked(int maxChecked) {
        max_checked = maxChecked;
    }

    void setMaxProbes(int maxProbes) {
        max_probes = maxProbes;
    }
};

#endif //ALGORITHMS_PROJECT_CUBE_H
