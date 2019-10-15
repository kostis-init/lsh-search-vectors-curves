#include <random>
#include <vector>
#include <cmath>
#include <cfloat>
#include "LSH.h"
#include "Curve.h"
#include "Point.h"
#include "hasher.h"




/*CurveHasher::CurveHasher() {
    numDimension = lsh->getDataset()->getDimension();
    int min = int(lsh->getDataset()->getMin());
    this->max = int(lsh->getDataset()->getMax());
    gridSize = 4 * numDimension * min;
    //TODO:set window properly
    phasher = new PointHasher(lsh->getNumOfFunctions(),max,1000);
    random_device r;
    //do we need another engine?
    default_random_engine e1(r());
    uniform_real_distribution<double> uniform_dist(0,numDimension);
    shiftedGrid = (double *)malloc(numDimension * sizeof(double));
    for (int i = 0; i < numDimension;i++) {
        shiftedGrid[i] = uniform_dist(e1);
    }
}*/

//assume ai = 1 i =1,2,..d (from slides)
CurveHasher::CurveHasher(int numDimension,int min,int max,int pointHasherWindow) {
    this->numDimension = numDimension;
    this->max = max;
    gridSize = 4 * numDimension * min;
    //TODO:set variables properly
    phasher = new PointHasher(3,max,pointHasherWindow);
    random_device r;
    //do we need another engine?
    default_random_engine e1(r());
    uniform_real_distribution<double> uniform_dist(0,numDimension);
    shiftedGrid = (double *)malloc(numDimension * sizeof(double));
    for (int i = 0; i < numDimension;i++) {
        shiftedGrid[i] = uniform_dist(e1);
    }
}

CurveHasher::~CurveHasher() {
    free(shiftedGrid);
    free(phasher);
}

size_t CurveHasher::operator() (Object *obj) const {
    Curve *curve = dynamic_cast<Curve *>(obj);
    auto point = vectorize(snap(curve));
    auto bucket =  (*phasher)(point);
    free(point);
    return bucket;
}

//transform grid curve (snapedCurve) to a vector which is 
//equivalent to a Point.
Point *CurveHasher::vectorize(double **snapedCurve) {
    vector<double> vec;
    double sumCoordinates = 0;
    int coefficient = 0xff;
    for (int i =0; i<max; i++) {
        if (i != 0 && isConsecutiveDuplitacate(snapedCurve,i))
            continue;
        for (int j =0; j < numDimension; j++) {
                //no fuss if overflows. Actually, we care only if 
                //we have two neighbours and one overflows e.g -1
                //and the other not e.g DBL_MAX. Then, despite they are 
                //neighbours, they will not be in the same bucket 
                //but this case is rare.
                //Moreover, we put some weight coefficient ^ j for every
                //coordinate. The spec doesn't mention this, but imo it 
                //is a good decision with the con that we increase propability
                //for overflow.
                sumCoordinates+= pow(coefficient,j) * snapedCurve[i][j]; 
            }
        vec.push_back(sumCoordinates);
        sumCoordinates = 0;
    }
    //free memory allocated in snap.
    for (int i =0; i < max; i++) 
        free(snapedCurve[i]);
    free(snapedCurve);
    return new Point(vec);
}

int CurveHasher::isConsecutiveDuplitacate(double **snapedCurve,int i) {
    for (int j =0; j < numDimension; j++) {
        if (snapedCurve[i][j] != snapedCurve[i-1][j])
            return 0;
    }
    return 1;
}

double **CurveHasher::snap(Curve *curve) {
    double **snapedCurve = (double **)malloc(max * sizeof(double *));
    for (int i=0; i< max; i++)
        snapedCurve[i] = snap(&curve->getPoint(i));
    return snapedCurve;
}

double *CurveHasher::snap(Point *point) {
    double *snapedPoint = (double *)malloc(numDimension * sizeof(double));
    for (int i = 0; i< numDimension; i++) {
        snapedPoint[i] = snap(point->getCoordinate(i),i);
    }
    return snapedPoint;
}

//round coordinate i of point(obj) to the nearest multiple
//of gridSize (starting from shiftedGrid[i]) and return the nearest multiple.
//Simpler solution than V2.
//Based on https://stackoverflow.com/questions/29557459/round-to-nearest-multiple-of-a-number
double CurveHasher::snap(double coordinate,int i) {
    double _gridSize = double(gridSize);
    double round =  coordinate + _gridSize/2.0;
    round -= fmod(round,_gridSize);
    double shiftDown = round - (_gridSize - shiftedGrid[i]);
    double shiftUp = round + shiftedGrid[i];
    if (fabs(coordinate - shiftUp) < fabs(coordinate - shiftDown)) {
        return shiftUp;
    }
    return shiftDown;
}

/*//not tested.
//round coordinate i of point(obj) to the nearest multiple
//of gridSize (starting from shiftedGrid[i]) and return the nearest multiple.
double CurveHasher::roundCoordinateV2(Point *point,int i) {
    double _gridSize = double(gridSize);
    auto remainder = abs(fmod(point->getCoordinate(i),_gridSize) - shiftedGrid[i]);
    auto minDist =  remainder < _gridSize/2.0 ? remainder : _gridSize - remainder;
    auto roundUp = minDist + point->getCoordinate(i);
    auto roundDown = minDist - point->getCoordinate(i);
    return fmod(roundUp,_gridSize) == 0.0 ? roundUp : roundDown;
}*/