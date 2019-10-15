#ifndef ALGORITHMS_PROJECT_HYPERCUBE_H
#define ALGORITHMS_PROJECT_HYPERCUBE_H

#include "LSH.h"

template <typename T>
class Hypercube : public LSH<T>{
private:
    int dimension = 3;
    int max_checked = 10;
    int max_probes = 2;
public:

    int getDimension() const {
        return dimension;
    }

    void setDimension(int dimension) {
        Hypercube::dimension = dimension;
    }

    int getMaxChecked() const {
        return max_checked;
    }

    void setMaxChecked(int maxChecked) {
        max_checked = maxChecked;
    }

    int getMaxProbes() const {
        return max_probes;
    }

    void setMaxProbes(int maxProbes) {
        max_probes = maxProbes;
    }

};

#endif //ALGORITHMS_PROJECT_HYPERCUBE_H
