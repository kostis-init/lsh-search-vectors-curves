#include "Point.h"

Point::Point(string id) {
    this->id = id;
}
Point::~Point() {

}

void Point::addCoordinateLast(double coordinate){
    this->coordinates.push_back(coordinate);
}

double Point::getCoordinate(int position){
    return this->coordinates.at(position);
}

std::vector<double> Point::getCoordinates() {
    return this->coordinates;
}
