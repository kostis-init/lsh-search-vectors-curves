#ifndef ALGORITHMS_PROJECT_UI_H
#define ALGORITHMS_PROJECT_UI_H
#include "Cube.h"

void readArgumentsLSHPoints(LSH* lsh, int argc, char **argv);
void readArgumentsLSHCurves(LSH* lsh, int argc, char **argv);
void readArgumentsCubePoints(Cube* cube, int argc, char **argv);
string askInputFile();
string askQueryFile();
string askOutputFile();

#endif //ALGORITHMS_PROJECT_UI_H
