#include <iostream>
#include <cmath>
#include "hasher.h"
#include "search.h"
#include "utils.h"
#include "Cube.h"
#include "ui.h"
#include "parse_files.h"

#define MAX_LEN 30

using namespace std;

int main(int argc, char* argv[]){
    auto cube = new Cube(new DTW());
    auto lsh = cube->getLsh();
    readArgumentsCubeCurves(cube, argc, argv);
    if(!lsh->isInputFileGiven())
        lsh->setInputFilename(askInputFile());
    if(!lsh->isQueryFileGiven())
        lsh->setQueryFilename(askQueryFile());
    if(!lsh->isOutputFileGiven())
        lsh->setOutputFilename(askOutputFile());
    lsh->setData(parseInputFileCurvesMaxLength(lsh->getInputFilename(), MAX_LEN));
    if(!cube->isDimensionGiven())
        cube->setDimension(log(lsh->getDataset()->getSize())/log(2));
    auto dataset = lsh->getDataset();
    lsh->setHashTableStruct(new CurveHashTableStruct(
        lsh->getNumOfHashTables(),lsh->getNumOfFunctions(),dataset->getDimension(),
        0.000002,dataset->getMax(),2));
    lsh->setQueryData(parseQueryFileCurvesMaxLength(lsh->getQueryFilename(), MAX_LEN));
    cube->createBinaryMaps();
    cube->createVertices();
    search_Cube_vs_BruteForce(cube);
    DoQueries(cube);
    return 0;
}
