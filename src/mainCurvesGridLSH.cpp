#include <iostream>
#include <iomanip>
#include <limits>
#include "HashTableStruct.h"
#include "Dataset.h"
#include "ui.h"
#include "parse_files.h"
#include "utils.h"
#include "LSH.h"
#include "hasher.h"
#include "distance.h"
#include "search.h"

#define MAX_LEN 50

LSH *LoadInput(int argc, char* argv[]) {
    auto lsh = new LSH(new DTW());
    readArgumentsLSHCurves(lsh, argc, argv);
    if(!lsh->isInputFileGiven())
        lsh->setInputFilename(askInputFile());
    if(!lsh->isQueryFileGiven())
        lsh->setQueryFilename(askQueryFile());
    if(!lsh->isOutputFileGiven())
        lsh->setOutputFilename(askOutputFile());
    lsh->setData(parseInputFileCurvesMaxLength(lsh->getInputFilename(),MAX_LEN));
    cout << lsh->getDataset()->getMean() << endl;
    //TODO:find formula for window and min
    auto dataset = lsh->getDataset();
    lsh->setHashTableStruct(new CurveHashTableStruct(lsh->getNumOfHashTables(),lsh->getNumOfFunctions(),dataset->getDimension(),0.000002,dataset->getMax(),2));
    auto points = lsh->getDataset()->getData();
    for (auto & point : points)
        lsh->getHashTableStruct()->addToAllHashTables(point);
    auto tables = lsh->getHashTableStruct()->getAllHashTables();
    for (int i =0; i < lsh->getNumOfHashTables(); i++)
        cout << "buckets: " << tables[i].bucket_count() << endl;
    lsh->setQueryData(parseQueryFileCurvesMaxLength(lsh->getQueryFilename(),MAX_LEN));
    return lsh;
}


int main(int argc, char* argv[]){
    auto lsh = LoadInput(argc,argv);
    search_LSH_vs_BruteForce(lsh);
    DoQueries(lsh);
}
