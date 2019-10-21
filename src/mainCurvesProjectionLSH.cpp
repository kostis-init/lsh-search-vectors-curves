#include <iostream>
#include "Projection.h"
#include "ui.h"
#include "parse_files.h"

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

    projection->setData(parseInputFileCurves(projection->getInputFilename()));
    projection->setQueryData(parseQueryFileCurves(projection->getQueryFilename()));


    return 0;
}