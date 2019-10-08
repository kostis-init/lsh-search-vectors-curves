#include "Point.h"

Point::Point() {

}

Point::~Point() {

}

void Point::addCoordinateLast(double co){
    coordinates.push_back(co);
}

double Point::getCoordinate(int position){
    return coordinates.at(position);
}

std::vector<double> Point::getCoordinates() {
    return coordinates;
}
