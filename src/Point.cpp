//
// Created by usw031 on 08/10/2019.
//

#include "Point.h"

Point::Point() {

}

Point::~Point() {

}

void Point::addCoordinateLast(int co){
    coordinates.push_back(co);
}

int Point::getCoordinate(int position){
    return coordinates.at(position);
}

std::vector<int> Point::getCoordinates() {
    return coordinates;
}
