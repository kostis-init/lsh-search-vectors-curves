#ifndef ALGORITHMS_PROJECT_DATASET_H
#define ALGORITHMS_PROJECT_DATASET_H
#include <vector>
#include "Point.h"
using namespace std;

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

class QueryDatasetPoints : public DatasetPoints {
private:

    double radius;

public:

    double getRadius();

    void setRadius(double radius);

};


#endif //ALGORITHMS_PROJECT_DATASET_H
