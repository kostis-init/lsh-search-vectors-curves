#ifndef ALGORITHMS_PROJECT_CURVE_H
#define ALGORITHMS_PROJECT_CURVE_H
#include <vector>
#include "Object.h"
#include "Point.h"

using namespace std;

class Curve : public Object{

private:

    string id;
    std::vector<Point> points;

public:

    Curve(string id);
    ~Curve();
    std::vector<Point> getPoints();
    string getId() {return id;}
};


#endif //ALGORITHMS_PROJECT_CURVE_H
