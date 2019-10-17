#include "search.h"
#include "distance.h"
#include <limits>
#include <bitset>

void search_points_Cube_vs_BruteForce(Cube* cube){

    int querySize = cube->getLsh()->getQueryData()->getSize();

    auto data = cube->getLsh()->getDataset()->getData();
    auto queryData = cube->getLsh()->getQueryData()->getData();

    for (int i = 0; i < querySize; ++i) {
        Point* queryPoint = (Point*)queryData.at(i);
        cout << "Query: " << queryPoint->getId() << endl;
        Point* nnPoint = nullptr;
        double distance;

        //Cube
        cout << "Cube" << endl;

        clock_t begin = clock();
        search_points_Cube(&nnPoint, &distance, queryPoint, cube);
        clock_t end = clock();

        if(nnPoint==nullptr){
            cout << "Nearest neighbor: Not Found" << endl;
        } else {
            cout << "Nearest neighbor Cube: " << nnPoint->getId() << endl;
            cout << "distance Cube: " << distance << endl;
            cout << "time Cube: " << end - begin << endl;
        }

        //Brute Force
        cout << "Brute Force" << endl;

        begin = clock();
        search_BruteForce(&nnPoint, &distance, data, queryPoint);
        end = clock();

        if(nnPoint==nullptr){
            cout << "Nearest neighbor: Not Found" << endl;
        } else {
            cout << "Nearest neighbor Brute Force: " << nnPoint->getId() << endl;
            cout << "distance Brute Force: " << distance << endl;
            cout << "time Brute Force: " << end - begin << endl << endl << endl;
        }

    }

}

void search_points_Cube(Point **nnPoint, double *distance, Point* queryPoint, Cube* cube) {
    random_device randomDevice;
    mt19937 mt(randomDevice());
    uniform_int_distribution<unsigned int> dist(0,1);

    auto binaryMaps = cube->getBinaryMaps();
    auto hashers = cube->getLsh()->getHashTableStruct()->getHashers();
    auto vertices = cube->getVertices();

    size_t index = 0;
    //construct index
    for (int i = 0; i < cube->getDimension(); ++i) {
        size_t hash = (*hashers.at(i))(queryPoint);
        index <<= 1u;
        if(binaryMaps[i].find(hash) != binaryMaps[i].end()){
            index |= binaryMaps[i].at(hash);
        }
        else{ //not found, produce random 0/1
            index |= dist(mt);
        }
    }

    int probes = cube->getMaxProbes();
    int limit = cube->getMaxChecked();
    size_t size = cube->getNumberOfVertices();
    size_t probe_index = index;
    size_t counter = 1;
    size_t basic_counter = 1;
    int base = 1;
    int adder = 0;
    *nnPoint = nullptr;
    *distance = numeric_limits<double>::max();

    //search on index (vertex), starting from current
    // and then go to vertices of hamming distance 1 (or 2, if 1 is exhausted)
    while(limit > 0 && probes >= 0){
        for(auto candidate : vertices[probe_index]){
            Point* candidatePoint = dynamic_cast<Point*>(candidate);
            double cur_dist;
            if( (cur_dist = manhattan(*queryPoint, *candidatePoint)) < *distance){
                *distance = cur_dist;
                *nnPoint = candidatePoint;
            }
            if(--limit <= 0)
                break;
        }
        // algorithm to change probe
        // works only for hamming distance 1 and 2
        //!!!WARNING: that means that max_probes must not be greater than (d' * (d'+1))/ 2
        if((basic_counter*2) > size ){
            adder = base;
            base *=2;
            basic_counter = base;
        }
        counter = basic_counter + adder;
        basic_counter *= 2;
        //bitset<30> x(counter); cout << x << endl;
        probe_index = index ^ counter;
        probes--;
    }
}

void search_points_LSH_vs_BruteForce(LSH* lsh) {
    auto hts = lsh->getHashTableStruct()->getAllHashTables();
    auto hashers = lsh->getHashTableStruct()->getHashers();
    int numOfHashTables = lsh->getNumOfHashTables();
    int querySize = lsh->getQueryData()->getSize();

    auto data = lsh->getDataset()->getData();
    auto queryData = lsh->getQueryData()->getData();

    for (int i = 0; i < querySize; ++i) {
        Point* queryPoint = (Point*)queryData.at(i);
        cout << "Query: " << queryPoint->getId() << endl;
        Point* nnPoint = nullptr;
        double distance;

        //LSH
        cout << "LSH" << endl;

        clock_t begin = clock();
        search_LSH(&nnPoint, &distance, numOfHashTables, hashers, queryPoint, hts);
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
        search_BruteForce(&nnPoint, &distance, data, queryPoint);
        end = clock();

        if(nnPoint==nullptr){
            cout << "Nearest neighbor: Not Found" << endl;
        } else {
            cout << "Nearest neighbor Brute Force: " << nnPoint->getId() << endl;
            cout << "distance Brute Force: " << distance << endl;
            cout << "time Brute Force: " << end - begin << endl << endl << endl;
        }
    }
}

void search_BruteForce(Point **nnPoint, double *distance, const vector<Object *>& data, Point *queryPoint) {
    *nnPoint = nullptr;
    *distance = numeric_limits<double>::max();
    for(auto candidate : data){
        Point* candidatePoint = dynamic_cast<Point*>(candidate);
        double cur_dist;
        if( (cur_dist = manhattan(*queryPoint, *candidatePoint)) < *distance){
            *distance = cur_dist;
            *nnPoint = candidatePoint;
        }
    }
}

void search_LSH(Point **nnPoint, double *distance, int numOfHashTables, vector<Hasher*> hashers, Point *queryPoint,
                unordered_map<int, vector<Object *>> *hts) {
    *nnPoint = nullptr;
    *distance = numeric_limits<double>::max();
    bool found = false;
    int threshold = 3 * numOfHashTables;
    int thresholdCount = 0;
    for (int j = 0; j < numOfHashTables; ++j) {
        size_t hash = (*hashers.at(j))(queryPoint);
        if(hts[j].find(hash) == hts[j].end()) //empty bucket
            continue;
        auto points = hts[j].at(hash);
        for(auto candidate : points){
            if (thresholdCount > threshold)
                break;
            Point* candidatePoint = dynamic_cast<Point*>(candidate);
            double cur_dist;
            //TODO: if large number of retrieved items (e.g. > 3L) then Break // exit loop
            if((cur_dist = manhattan(*queryPoint, *candidatePoint)) < *distance){
                found = true;
                *distance = cur_dist;
                *nnPoint = candidatePoint;
            }
            thresholdCount++;
        }
    }
    //if we fall in empty backet for all htables
    //set dist to zero (otherwise AF calculation is useless)
    if (!found)
        *distance = 0.0;
}
