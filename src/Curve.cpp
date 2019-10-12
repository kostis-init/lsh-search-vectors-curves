#include "Curve.h"

Curve::Curve(string id) : Object(id) {}

Curve::~Curve() {

}

std::vector<Point> Curve::getPoints() {
    return points;
}