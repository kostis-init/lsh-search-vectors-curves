#ifndef ALGORITHMS_PROJECT_UI_H
#define ALGORITHMS_PROJECT_UI_H
#include "Cube.h"

void readArgumentsLSH(LSH<PointHasher>* lsh, int argc, char **argv);
void readArgumentsCube(Cube<PointHasher>* cube, int argc, char **argv);
void askInputFile();
void askQueryFile();
void askOutputFile();

#endif //ALGORITHMS_PROJECT_UI_H
