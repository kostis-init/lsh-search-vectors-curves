#ifndef ALGORITHMS_PROJECT_SEARCH_H
#define ALGORITHMS_PROJECT_SEARCH_H

#include "Dataset.h"
#include "LSH.h"
#include "Cube.h"

void search_points_Cube_vs_BruteForce(Cube* cube);
void search_points_Cube(Point **nnPoint, double *distance, Point* queryPoint, Cube* cube);

void search_points_LSH_vs_BruteForce(LSH* lsh);
void search_BruteForce(Point **nnPoint, double *distance, const vector<Object *>& data, Point *queryPoint);
void search_LSH(Point **nnPoint, double *distance, int numOfHashTables, vector<Hasher*> hashers,
                Point *queryPoint, unordered_map<int, vector<Object *>> *hts);


#endif //ALGORITHMS_PROJECT_SEARCH_H
