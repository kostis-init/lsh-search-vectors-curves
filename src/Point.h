#ifndef ALGORITHMS_PROJECT_POINT_H
#define ALGORITHMS_PROJECT_POINT_H

#include <vector>

class Point {

private:

    std::vector<int> coordinates;

public:

    Point();
    ~Point();
    void addCoordinateLast(int co);
    int getCoordinate(int position);
    std::vector<int> getCoordinates();

};


#endif //ALGORITHMS_PROJECT_POINT_H
