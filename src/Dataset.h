#ifndef ALGORITHMS_PROJECT_DATASET_H
#define ALGORITHMS_PROJECT_DATASET_H
#include <vector>
#include "Point.h"
using namespace std;

class Dataset {
    private:
        int dimension;
        int size;
        double min;
        double max;
        int mean;
        vector<Object *> data;
    public:
        Dataset(vector<Object *> data);
        Dataset(){};
        void setSize(int sz);
        void setMax(double max);
        void setMin(double min);
        void setMean(int mean);
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
        int getMean();
};

class QueryDataset : public Dataset {
private:
    double radius;
public:
    double getRadius();
    void setRadius(double radius);
};

#endif //ALGORITHMS_PROJECT_DATASET_H
