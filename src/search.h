#ifndef ALGORITHMS_PROJECT_SEARCH_H
#define ALGORITHMS_PROJECT_SEARCH_H

#include "Dataset.h"
#include "LSH.h"
#include "Cube.h"

void search_Cube_vs_BruteForce(Cube* cube);
void search_LSH_vs_BruteForce(LSH* lsh);

void search_Cube(Object **nearestNeighbor, double *distance, Object* queryObject, Cube* cube, vector<Object*>& radiusNeighbors, double radius);
void search_LSH(Object **nearestNeighbor, double *distance, Object *queryObject, LSH* lsh, vector<Object*>& radiusNeighbors, double radius);
void search_BruteForce(Object **nnObj, double *distance, const vector<Object *>& data, Object *queryPoint,DistanceMetric *dmetric);

void DoQueries(LSH *lsh);
void DoQueries(Cube *cube);

#endif //ALGORITHMS_PROJECT_SEARCH_H
