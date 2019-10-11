#include <iostream>
#include "HashTableStruct.h"
#include "Dataset.h"
#include "ui.h"
#include "parse_files.h"
#include "utils.h"
#include "LSH.h"

using namespace std;

LSH* lsh;

int main(int argc, char* argv[]){

    lsh = new LSH();

    /**
     * read arguments
     */
    readArgumentsLSH(argc, argv);

    /**
     * ask input filename (if not given as an argument)
     */
    if(!lsh->isInputFileGiven())
        askInputFile();

    /**
     * parse input file into memory
     */
    lsh->setData(parseInputFilePoints(lsh->getInputFilename()));
    //test_print_data(lsh->getData());

    /**
     * insert data into hash tables
     */
    cout << "Constructing hash table..." << endl;
    auto hashTableStruct = new HashTableStruct(lsh->getNumOfHashTables());
    auto points = lsh->getData()->getPoints();
    for (int i = 0; i < points.size(); i++)
        hashTableStruct->addToAllHashTables(points[i]);
    //test_print_hashtable(hashTableStruct);

    /**
     * ask query filename and output filename (if not given as arguments)
     */
    if(!lsh->isQueryFileGiven())
        askQueryFile();
    if(!lsh->isOutputFileGiven())
        askOutputFile();

    /**
     * parse query file into memory
     */
     lsh->setQueryData(parseQueryFilePoints(lsh->getQueryFilename()));
    //test_print_query_data(lsh->getQueryData());


    //do the query, output the results

    //ask user if he wants another one

    // +check memory leaks

    return 0;
}

