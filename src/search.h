#ifndef ALGORITHMS_PROJECT_SEARCH_H
#define ALGORITHMS_PROJECT_SEARCH_H

#include "Dataset.h"
#include "LSH.h"
#include "Cube.h"

void search_points_Cube_vs_BruteForce(Cube* cube);
void search_points_Cube(Point **nnPoint, double *distance, Point* queryPoint, Cube* cube);
void search_BruteForce_Cube(Object **nnObj, double *distance, const vector<Object *>& data, Object *queryObj);

void search_LSH_vs_BruteForce(LSH* lsh);
void search_BruteForce(Object **nnObj, double *distance, const vector<Object *>& data, Object *queryPoint,DistanceMetric *dmetric);
void search_LSH(Object **nnPoint, double *distance, int numOfHashTables, vector<Hasher*> hashers,
                Object *queryPoint, unordered_map<int, vector<Object *>> *hts,DistanceMetric *dmetric);

void DoQueries(LSH *lsh);

#endif //ALGORITHMS_PROJECT_SEARCH_H
