#ifndef ALGORITHMS_PROJECT_DATASET_H
#define ALGORITHMS_PROJECT_DATASET_H
#include <vector>
#include "Point.h"
using namespace std;


//Trying to generalize things.
class Dataset {
    private:
        int dimension;
        int size;
        double min;
        double max;
        vector<Object *> data;
    public:
        void setSize(int sz);
        void setDimension(int d);
        void add(Object *obj);
        vector<Object *> getData();
        int getSize();
        int getDimension();
        //min coordinate for points 
        //min length for curves
        double getMin();
        //max coordinate for points 
        //max length for curves
        double getMax();
        void setMin(double);
        void setMax(double);
};

/*
class DatasetPoints {
private:
    int dimension;
    int size;
    double minCoordinate;
    double maxCoordinate;
    vector<Point *> points;
public:
    void setSize(int sz);
    void setDimension(int d);
    void addPoint(Point *point);
    vector<Point *> getPoints();
    int getDimension();
    int getSize();
    double getMinCoordinate();
    double getMaxCoordinate();
    void setMinCoordinate(double);
    void setMaxCoordinate(double);
};
*/

class QueryDataset : public Dataset {
private:
    double radius;
public:
    double getRadius();
    void setRadius(double radius);
};

#endif //ALGORITHMS_PROJECT_DATASET_H
