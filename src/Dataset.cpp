#include "Dataset.h"

void DatasetPoints::setSize(int sz) {
    this->size = sz;
}

void DatasetPoints::setDimension(int d) {
    this->dimension = d;
}

void DatasetPoints::addPoint(Point *point) {
    this->points.push_back(point);
}

vector<Point *> DatasetPoints::getPoints() {
    return this->points;
}

int DatasetPoints::getDimension() {
    return dimension;
}

int DatasetPoints::getSize() {
    return size;
}

double QueryDatasetPoints::getRadius() {
    return radius;
}

void QueryDatasetPoints::setRadius(double radius) {
    this->radius = radius;
}
