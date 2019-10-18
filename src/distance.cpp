//#include <cmath>
#include <math.h>
#include <cfloat>
#include "distance.h"
#include "LSH.h"

double Manhattan::dist(Object *obj1,Object *obj2){
    auto p1 = dynamic_cast<Point *>(obj1);
    auto p2 = dynamic_cast<Point *>(obj2);
    if (p1->getCoordinates().size() != p2->getCoordinates().size())
        return -1;
    double sum = 0;
    int sz = p1->getCoordinates().size();
    for(int i =0; i < sz;i++)
        sum += fabs(p1->getCoordinate(i) - p2->getCoordinate(i));
    return sum;
}

double euclidean(Point p1,Point p2) {
    if (p1.getCoordinates().size() != p2.getCoordinates().size())
        return -1;
    double dist;
    double sum = 0.0;
    for (int i=0; i < p1.getCoordinates().size(); i++) {
        dist = p1.getCoordinate(i) - p2.getCoordinate(i);
        sum += dist*dist;
    }
    return sqrt(sum);
}

double DTW::dist(Object *obj1,Object *obj2){
    auto c1 = dynamic_cast<Curve *>(obj1);
    auto c2 = dynamic_cast<Curve *>(obj2);
    auto c1Len = c1->getPoints().size();
    auto c2Len = c2->getPoints().size();
    double **arr = new double*[c1Len];
    for (int i =0; i < c1Len; i++)
        arr[i] = new double[c2Len];
    for (int i =0; i < c1Len; i++) {
        for (int j =0; j < c2Len; j++) {
            if (!i && !j) //both zero
                arr[i][j] = euclidean(c1->getPoint(i),c2->getPoint(j));
            else if (!i) 
                arr[i][j] = arr[i][j-1] + euclidean(c1->getPoint(i),c2->getPoint(j));
            else if (!j)
                arr[i][j] = arr[i-1][j] + euclidean(c1->getPoint(i),c2->getPoint(j));
            else 
                arr[i][j] = min(arr[i][j-1],min(arr[i-1][j],arr[i-1][j-1])) + euclidean(c1->getPoint(i),c2->getPoint(j));
        }
    }
    return arr[c1Len-1][c2Len-1];
}