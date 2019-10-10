#ifndef ALGORITHMS_PROJECT_UI_H
#define ALGORITHMS_PROJECT_UI_H
#include "HashTableStruct.h"
#include "LSH.h"
#include "Dataset.h"

void readArgumentsLSH(LSH* lsh, int argc, char **argv);
void askInputFile(LSH* lsh);
DatasetPoints* parseInputFilePoints(string filename);
void askQueryFile(LSH* lsh);
void askOutputFile(LSH* lsh);
QueryDatasetPoints* parseQueryFilePoints(string filename);

#endif //ALGORITHMS_PROJECT_UI_H
