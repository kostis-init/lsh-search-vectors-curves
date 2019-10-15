#include <iostream>
#include "hasher.h"
#include "Cube.h"
#include "ui.h"
#include "parse_files.h"

using namespace std;

int main(int argc, char* argv[]){

    auto cube = new Cube();
    auto lsh = cube->getLsh();
    /**
     * read arguments
     */
    readArgumentsCube(cube, argc, argv);

    /**
     * ask input filename (if not given as an argument)
     */
    if(!lsh->isInputFileGiven())
        lsh->setInputFilename(askInputFile());

    /**
     * parse input file into memory
     */
    lsh->setData(parseInputFilePoints(lsh->getInputFilename()));
    //test_print_data(lsh->getData());

    /**
    * insert data into hash tables
    */
    cout << "Constructing hash table..." << endl;
lsh->setHashTableStruct(new PointHashTableStruct(lsh->getNumOfHashTables(), lsh->getDataset()->getSize(),lsh->getNumOfFunctions(),lsh->getDataset()->getDimension(),lsh->getDataset()->getMean()));
    auto points = lsh->getDataset()->getData();
    for (auto & point : points)
        lsh->getHashTableStruct()->addToAllHashTables(point);
    //lsh->getHashTableStruct()->test_print_hashtable();

    /**
    * ask query filename and output filename (if not given as arguments)
    */
    if(!lsh->isQueryFileGiven())
        lsh->setQueryFilename(askQueryFile());
    if(!lsh->isOutputFileGiven())
        lsh->setOutputFilename(askOutputFile());

    /**
    * parse query file into memory
    */
    lsh->setQueryData(parseQueryFilePoints(lsh->getQueryFilename()));
    //test_print_query_data(lsh->getQueryData());

    //TODO: now do the cube thing...


    //ask user if he wants another one

    // +check memory leaks

    return 0;
}
