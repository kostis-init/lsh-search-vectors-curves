#ifndef ALGORITHMS_PROJECT_CURVE_H
#define ALGORITHMS_PROJECT_CURVE_H
#include <vector>
#include "Object.h"
#include "Point.h"

class Curve : Object{

private:

    std::vector<Point> points;

public:

    Curve();
    ~Curve();
    std::vector<Point> getPoints();

};


#endif //ALGORITHMS_PROJECT_CURVE_H
