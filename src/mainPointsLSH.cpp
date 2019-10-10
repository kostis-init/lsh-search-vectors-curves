#include <iostream>
#include "HashTableStruct.h"
#include "Dataset.h"
#include "ui.h"
#include "utils.h"
#include "LSH.h"

using namespace std;

LSH* lsh;

int main(int argc, char* argv[]){

    lsh = new LSH();

    /**
     * read arguments
     */
    readArgumentsLSH(lsh, argc, argv);

    /**
     * ask input filename (if not given as an argument)
     */
    if(!lsh->isInputFileGiven())
        askInputFile(lsh);

    /**
     * read input file and store data in memory
     */
    lsh->setData(parseInputFilePoints(lsh->getInputFilename()));
    //test_print_data(lsh->getData());

    /**
     * insert data into hash tables
     */
    auto hashTableStruct = new HashTableStruct(lsh->getNumOfHashTables());
    auto points = lsh->getData()->getPoints();
    for (int i = 0; i < points.size(); i++) {
        hashTableStruct->addToAllHashTables(points[i]);
    }
    test_print_hashtable(hashTableStruct);

    //ask for query file and output file if not given as arguments

    //do the query, output the results

    //ask user if he wants another one

    // +check memory leaks

    return 0;
}

