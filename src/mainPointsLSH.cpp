#include <iostream>
#include "HashTableStruct.h"
#include "Dataset.h"
#include "ui.h"
#include "utils.h"
#include "LSH.h"

using namespace std;

void test_print_hashtable(HashTableStruct *hashTableStruct) {
    auto hts = hashTableStruct->getAllHashTables();
    for (int i = 0; i < hashTableStruct->getNumOfHTs(); ++i) {
        auto fn = hts[i].hash_function();
        cout << "Checking hash table " << i + 1 << endl;
        for(auto entry : hts[i]){
            cout << entry->getId() << " hash func: " << fn(entry) << ", bucket #" << hts[i].bucket(entry)<< endl;
        }
    }
}
void test_print_data(DatasetPoints *data) {
    auto points = data->getPoints();
    for (int i = 0; i < points.size(); i+=100) {
        cout << "CHECKING ITEM ID: " << points[i]->getId() << endl;
        auto coords = points[i]->getCoordinates();
        for (int j = 0; j < coords.size(); ++j) {
            cout << coords[j] << " ";
        }
        cout << endl;
    }
    cout << data->getDimension() << " " << data->getSize() << endl;
}

int main(int argc, char* argv[]){

    auto lsh = new LSH();

    //read input arguments
    readArgumentsLSH(lsh, argc, argv);

    //ask for input file if not given as argument

    //read input file and store data in memory
    parseInputFilePoints(lsh);
    test_print_data(lsh->getData());

    //construct hash tables & hash functions
    auto hashTableStruct = new HashTableStruct(lsh->getNumOfHashTables());

    //insert points to hash tables
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

