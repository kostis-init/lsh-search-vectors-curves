#ifndef DISTANCE_H
#define DISTANCE_H
#include "Point.h"

class DistanceMetric {
    public:
    virtual double dist(Object* obj1,Object *obj2) = 0;
};

class Manhattan : public DistanceMetric {
    public:
    double dist(Object *obj1,Object *obj2);
};

class DTW : public DistanceMetric {
    public:
    double dist(Object *obj1,Object *obj2);
};

//leave this here because Cube depends on this 
//to be removed soon
double manhattan(Object *obj1,Object *obj2);

#endif