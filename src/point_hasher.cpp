#include <stdlib.h>
#include <random>
#include <iostream>
#include <vector>
#include  <stdio.h>
#include "hasher.h"
//#include "Object.h"
#include "Point.h"
#include "utils.h"
#include "Dataset.h"
#include "LSH.h"

using namespace std;

extern LSH* lsh;

double **PointHasher::gridPool;

//TODO: set window size based on dataset (for better point grouping).
//needs to be done inside lsh. We could set it based on some metrics e.g. 
//based on the highest coordinate of a point and minimum (generally based 
//on change-variation of points).
PointHasher::PointHasher() {
    amplificationSize = lsh->getNumOfFunctions();
    numDimension = lsh->getData()->getDimension();
    partialHashRange = pow(2,int(32/amplificationSize));
    if (gridPool == nullptr) {
        generateGrids();
    }
    random_device r;
    //do we need another engine?
    default_random_engine e1(r());
    uniform_int_distribution<int> uniform_dist(0,gridPoolSize-1);
    selectedGrids = (int *)malloc(gridPoolSize * sizeof(int));
    for (int i = 0; i<amplificationSize; i++){
        selectedGrids[i] = uniform_dist(e1);
    }
}

//debug
PointHasher::PointHasher(int ampSize,int numDimension,int window) {
    this->amplificationSize = ampSize;
    this->numDimension = numDimension;
    this->window = window;
    partialHashRange = pow(2,int(32/amplificationSize));
    if (gridPool == nullptr) {
        generateGrids();
    }
    random_device r;
    //do we need another engine?
    default_random_engine e1(r());
    uniform_int_distribution<int> uniform_dist(0,gridPoolSize-1);
    selectedGrids = (int *)malloc(amplificationSize * sizeof(int));
    for (int i = 0; i<amplificationSize; i++){
        selectedGrids[i] = uniform_dist(e1);
    }
}

//dont free gridPool (static)
PointHasher::~PointHasher() {
    free(selectedGrids);
}

void PointHasher::generateGrids() {
    random_device r;
    //do we need another engine?
    default_random_engine e1(r());
    uniform_real_distribution<float> uniform_dist(0, window);
    gridPool = (double **) malloc(gridPoolSize * sizeof(double *));
    for (int i = 0; i < gridPoolSize; i++)
        gridPool[i] = (double *) malloc(numDimension * sizeof(double));
    for (int i = 0; i < gridPoolSize; i++)
        for (int j = 0; j < numDimension; j++) {
            gridPool[i][j] = uniform_dist(e1);
        }
}

int PointHasher::hash(Object* obj,int hashIndex) const {
    Point *point = dynamic_cast<Point *>(obj);
    vector<double> coordinates = point->getCoordinates();
    //or select coefficient randomly?
    int coefficient = 0xffff;
    unsigned int sum = 0,i = 0,j = numDimension;
    //sum may overflow if amplificationSize is too small and
    //if numDimension is too high but no fuss - uint will wrap around.
    for (auto c :coordinates) {
        unsigned int gridCell = int((c - gridPool[selectedGrids[hashIndex]][i])/window);
        sum+= ((gridCell%partialHashRange)*(powModulo(coefficient,j,partialHashRange)))%partialHashRange;
        i++;
        j--;
    }
    return sum % partialHashRange;
}

size_t PointHasher::operator()(Object *obj) const {
    int numPartialHashBits = 32/amplificationSize;
    int res = 0;
    int partialHash;
    //calculate each partial hash and concanate them in res
    for (int i =0; i < amplificationSize; i++) {
        partialHash = hash(obj,i);
        res |= partialHash << i*4;
    }
    return res;
}