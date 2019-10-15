#include <iostream>
#include <limits.h>
#include "HashTableStruct.h"
#include "Dataset.h"
#include "ui.h"
#include "parse_files.h"
#include "utils.h"
#include "LSH.h"
#include "hasher.h"

using namespace std;

LSH<PointHasher>* lsh;

int main(int argc, char* argv[]){

    lsh = new LSH<PointHasher>;

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
    cout << "omg" << endl;
    lsh->setData(parseInputFilePoints(lsh->getInputFilename()));
    cout << lsh->getDataset()->getMean() << endl;
    cout << "omg" << endl;
    //test_print_data(lsh->getData());

    /**
     * insert data into hash tables
     */
    cout << "Constructing hash table..." << endl;
    lsh->setHashTableStruct(new HashTableStruct<PointHasher>(lsh->getNumOfHashTables(), lsh->getDataset()->getSize()));
    //lsh->setHashTableStruct(new HashTableStruct<PointHasher>(lsh->getNumOfHashTables()));
    auto points = lsh->getDataset()->getData();
    for (int i = 0; i < points.size(); i++)
        lsh->getHashTableStruct()->addToAllHashTables(points[i]);
    lsh->getHashTableStruct()->test_print_hashtable();

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

    /**
     * search
     */
//     QueryDataset* query = lsh->getQueryData();
//    for (int i = 0; i < query->getSize(); ++i) {
//        cout << "Query: " << query->getData().at(i)->getId() << endl;
//        Point* winner = nullptr;
//        int distance = INT_MAX;
//        auto hts = lsh->getHashTableStruct()->getAllHashTables();
//        for (int j = 0; j < lsh->getNumOfHashTables(); ++j) {
//            //hash function or bucket???
//            for(auto iter = hts[j].begin(hts[j].bucket(query->getData().at(i))); iter != hts[j].end(hts[j].bucket(query->getData().at(i))); ++iter){
//                cout << (*iter)->getId() << hts[j].bucket(query->getData().at(i)) << " " << hts[j].bucket(*iter) << endl;
//            }
//        }
//    }


    //ask user if he wants another one

    // +check memory leaks

    return 0;
}

