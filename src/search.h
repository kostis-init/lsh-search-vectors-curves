#ifndef ALGORITHMS_PROJECT_SEARCH_H
#define ALGORITHMS_PROJECT_SEARCH_H

#include "Dataset.h"
#include "LSH.h"

void search_points_LSH_vs_BruteForce(LSH<PointHasher>* lsh);
void search_BruteForce(Point **nnPoint, double *distance, const vector<Object *>& data, Point *queryPoint);
void search_LSH(Point **nnPoint, double *distance, int numOfHashTables, PointHasher *hashers,
                Point *queryPoint, unordered_map<int, vector<Object *>> *hts);


#endif //ALGORITHMS_PROJECT_SEARCH_H
