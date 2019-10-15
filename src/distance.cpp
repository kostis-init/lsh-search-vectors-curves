#include <cmath>
#include <cfloat>
#include "distance.h"
#include "LSH.h"

double manhattan(Point p1,Point p2){
    if (p1.getCoordinates().size() != p2.getCoordinates().size())
        return -1;
    double sum = 0;
    int sz = p1.getCoordinates().size();
    for(int i =0; i < sz;i++)
        sum += fabs(p1.getCoordinate(i) - p2.getCoordinate(i));
    return sum;
}

