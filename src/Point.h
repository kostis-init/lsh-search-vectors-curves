#ifndef ALGORITHMS_PROJECT_POINT_H
#define ALGORITHMS_PROJECT_POINT_H
#include <vector>
#include "Object.h"

class Point : Object{

private:

    std::vector<double> coordinates;

public:

    Point();
    ~Point();
    void addCoordinateLast(double co);
    double getCoordinate(int position);
    std::vector<double> getCoordinates();

};


#endif //ALGORITHMS_PROJECT_POINT_H
