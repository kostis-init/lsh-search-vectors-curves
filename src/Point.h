#ifndef ALGORITHMS_PROJECT_POINT_H
#define ALGORITHMS_PROJECT_POINT_H
#include <vector>
#include <string>
#include "Object.h"
using namespace std;
class Point : Object{

private:

    string id;
    vector<double> coordinates;

public:

    Point(string id);
    ~Point();
    void foo(){}
    void addCoordinateLast(double coordinate);
    double getCoordinate(int position);
    std::vector<double> getCoordinates();
    string getId(){return this->id;}

};


#endif //ALGORITHMS_PROJECT_POINT_H
