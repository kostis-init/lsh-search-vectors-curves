#ifndef ALGORITHMS_PROJECT_DATASET_H
#define ALGORITHMS_PROJECT_DATASET_H
#include <vector>
#include "Point.h"
using namespace std;

class DatasetPoints {

private:

    int dimension;
    int size;
    vector<Point *> points;

public:

    DatasetPoints();
    ~DatasetPoints();

    void setSize(int sz);
    void setDimension(int d);
    void addPoint(Point *point);

    vector<Point *> getData();
    int getDimension();
    int getSize();
};




#endif //ALGORITHMS_PROJECT_DATASET_H
