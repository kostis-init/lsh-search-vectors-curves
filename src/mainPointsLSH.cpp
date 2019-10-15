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

using namespace std;

LSH* lsh;

int main(int argc, char* argv[]){

    lsh = new LSH;

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
    lsh->setHashTableStruct(new PointHashTableStruct(lsh->getNumOfHashTables(), lsh->getDataset()->getSize(),lsh->getNumOfFunctions(),lsh->getDataset()->getDimension(),lsh->getDataset()->getMean()));
    auto points = lsh->getDataset()->getData();
    for (auto & point : points)
        lsh->getHashTableStruct()->addToAllHashTables(point);
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
    QueryDataset* query = lsh->getQueryData();
    auto hts = lsh->getHashTableStruct()->getAllHashTables();
    auto hashers = lsh->getHashTableStruct()->getHashers();
    int sz = lsh->getNumOfHashTables();
    auto data = lsh->getDataset()->getData();

    for (int i = 0; i < query->getSize(); ++i) {
        Point* queryPoint = (Point*)query->getData().at(i);
        cout << "Query: " << queryPoint->getId() << endl;

        //LSH
        cout << "LSH" << endl;
        clock_t begin = clock();
        Point* nnPoint = nullptr;
        double distance = numeric_limits<double>::max();
        for (int j = 0; j < sz; ++j) {
            //size_t hash = hashers[j](queryPoint);
            size_t hash = (*hashers.at(j))(queryPoint);
            if(hts[j].find(hash) == hts[j].end()) //empty bucket
                continue;
            auto points = hts[j].at(hash);
            for(auto candidate : points){
                Point* candidatePoint = dynamic_cast<Point*>(candidate);
                double cur_dist;
                //TODO: if large number of retrieved items (e.g. > 3L) then Break // exit loop
                if((cur_dist = manhattan(*queryPoint, *candidatePoint)) < distance){
                    distance = cur_dist;
                    nnPoint = candidatePoint;
                }
            }
        }
        clock_t end = clock();
        if(nnPoint==nullptr){
            cout << "Nearest neighbor: Not Found" << endl;
        } else {
            cout << "Nearest neighbor LSH: " << nnPoint->getId() << endl;
            cout << "distance LSH: " << distance << endl;
            cout << "time LSH: " << end - begin << endl;
        }

        //Brute Force
        cout << "Brute Force" << endl;
        begin = clock();
        nnPoint = nullptr;
        distance = numeric_limits<double>::max();
        for(auto candidate : data){
            Point* candidatePoint = dynamic_cast<Point*>(candidate);
            double cur_dist;
            if( (cur_dist = manhattan(*queryPoint, *candidatePoint)) < distance){
                distance = cur_dist;
                nnPoint = candidatePoint;
            }
        }
        end = clock();
        if(nnPoint==nullptr){
            cout << "Nearest neighbor: Not Found" << endl;
        } else {
            cout << "Nearest neighbor Brute Force: " << nnPoint->getId() << endl;
            cout << "distance Brute Force: " << distance << endl;
            cout << "time Brute Force: " << end - begin << endl << endl << endl;
        }

    }


    //ask user if he wants another one

    // +check memory leaks

    return 0;
}

