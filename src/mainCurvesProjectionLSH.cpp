#include <iostream>
#include "Projection.h"
#include "ui.h"
#include "parse_files.h"

#define MAX_LENGTH 9

using namespace std;

int main(int argc, char* argv[]){

    auto projection = new Projection();

    readArgumentsLSHProjectionCurves(projection, argc, argv);
    if(!projection->isInputFileGiven())
        projection->setInputFilename(askInputFile());
    if(!projection->isQueryFileGiven())
        projection->setQueryFilename(askQueryFile());
    if(!projection->isOutputFileGiven())
        projection->setOutputFilename(askOutputFile());

    projection->setData(parseInputFileCurvesMaxLength(projection->getInputFilename(), MAX_LENGTH));
    projection->setQueryData(parseQueryFileCurvesMaxLength(projection->getQueryFilename(), MAX_LENGTH));

    //WARNING! bigger size may crash your pc
    projection->buildTraversalsMatrix(MAX_LENGTH);

    //TODO: hashing and searching

    return 0;
}