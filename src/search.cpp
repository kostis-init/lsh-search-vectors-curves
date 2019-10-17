#include "search.h"
#include "distance.h"
#include <limits>

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
        search_BruteForce_Cube(&nnPoint, &distance, data, queryPoint);
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
    uniform_int_distribution<int> dist(0,1);

    auto binaryMaps = cube->getBinaryMaps();
    auto hashers = cube->getLsh()->getHashTableStruct()->getHashers();
    auto vertices = cube->getVertices();

    int index = 0;
    //construct index
    for (int i = 0; i < cube->getDimension(); ++i) {
        int hash = (*hashers.at(i))(queryPoint);
        index <<= 1;
        if(binaryMaps[i].find(hash) != binaryMaps[i].end()){
            index |= binaryMaps[i].at(hash);
        }
        else{ //not found, produce random 0/1
            index |= dist(mt);
        }
    }

    int probes = cube->getMaxProbes();
    int limit = cube->getMaxChecked();
    int size = cube->getNumberOfVertices();
    int probe_index = index;
    int counter = 1;

    *nnPoint = nullptr;
    *distance = numeric_limits<double>::max();

    while(limit > 0 && probes >= 0){
        cout << probes << endl;
        for(auto candidate : vertices[probe_index]){
            Point* candidatePoint = dynamic_cast<Point*>(candidate);
            double cur_dist;
            if( (cur_dist = manhattan(queryPoint, candidatePoint)) < *distance){
                *distance = cur_dist;
                *nnPoint = candidatePoint;
            }
            limit--;
            if(limit <= 0)
                break;
        }
        //!!!!!!!!!!!!!!!!!!!!!!!!!
        //TODO: probes need work!!!
        //!!!!!!!!!!!!!!!!!!!!!!!!!
        probe_index = index ^ counter;

        if((counter*2) >= size ){

        }else
            counter *= 2;
        probes--;
    }
}

void search_BruteForce_Cube(Object **nnObj, double *distance, const vector<Object *>& data, Object *queryObj) {
    *nnObj = nullptr;
    *distance = numeric_limits<double>::max();
    for(auto candidate : data){
        double cur_dist;
        if( (cur_dist = manhattan(queryObj, candidate)) < *distance){
            *distance = cur_dist;
            *nnObj = candidate;
        }
    }
}

void search_LSH_vs_BruteForce(LSH* lsh) {
    auto hts = lsh->getHashTableStruct()->getAllHashTables();
    auto hashers = lsh->getHashTableStruct()->getHashers();
    int numOfHashTables = lsh->getNumOfHashTables();
    int querySize = lsh->getQueryData()->getSize();
    auto metric = lsh->getMetric();
    auto data = lsh->getDataset()->getData();
    auto queryData = lsh->getQueryData()->getData();

    for (int i = 0; i < querySize; ++i) {
        Object* queryPoint = (Point*)queryData.at(i);
        cout << "Query: " << queryPoint->getId() << endl;
        Object* nnPoint = nullptr;
        double distance;

        //LSH
        cout << "LSH" << endl;

        clock_t begin = clock();
        search_LSH(&nnPoint, &distance, numOfHashTables, hashers, queryPoint, hts,metric);
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
        search_BruteForce(&nnPoint, &distance, data, queryPoint,metric);
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

void search_BruteForce(Object **nnObj, double *distance, const vector<Object *>& data, Object *queryObj,DistanceMetric *dmetric) {
    *nnObj = nullptr;
    *distance = numeric_limits<double>::max();
    for(auto candidate : data){
        //Point* candidatePoint = dynamic_cast<Point*>(candidate);
        double cur_dist;
        if( (cur_dist = dmetric->dist(queryObj, candidate)) < *distance){
            *distance = cur_dist;
            *nnObj = candidate;
        }
    }
}

void search_LSH(Object **nnPoint, double *distance, int numOfHashTables, vector<Hasher*> hashers, Object *queryPoint,
                unordered_map<int, vector<Object *>> *hts,DistanceMetric *dmetric) {
    *nnPoint = nullptr;
    *distance = numeric_limits<double>::max();
    bool found = false;
    int threshold = 50 * numOfHashTables;
    int thresholdCount = 0;
    for (int j = 0; j < numOfHashTables; ++j) {
        size_t hash = (*hashers.at(j))(queryPoint);
        if(hts[j].find(hash) == hts[j].end()) //empty bucket
            continue;
        auto points = hts[j].at(hash);
        for(auto candidate : points){
            if (thresholdCount > threshold)
                break;
            double cur_dist;
            //TODO: if large number of retrieved items (e.g. > 3L) then Break // exit loop
            if((cur_dist = dmetric->dist(queryPoint, candidate)) < *distance){
                found = true;
                *distance = cur_dist;
                *nnPoint = candidate;
            }
            thresholdCount++;
        }
    }
    //if we fall in empty backet for all htables
    //set dist to zero (otherwise AF calculation is useless)
    if (!found)
        *distance = 0.0;
}

void DoQueries(LSH *lsh) {
    auto hts = lsh->getHashTableStruct()->getAllHashTables();
    auto hashers = lsh->getHashTableStruct()->getHashers();
    int numOfHashTables = lsh->getNumOfHashTables();
    int querySize = lsh->getQueryData()->getSize();
    auto data = lsh->getDataset()->getData();
    auto queryData = lsh->getQueryData()->getData();
    auto metric = lsh->getMetric();
    clock_t meanSearchLSH = 0;
    clock_t meanSearchBF = 0;
    double maxAF = numeric_limits<double>::min();
    double averageAF = 0;
    int averageAFCount = 0;
    for (int i = 0; i < querySize; ++i) {
        Object* queryPoint = (Point*)queryData.at(i);
        Object* nnPoint;
        double distanceLSH;
        double distanceBF;
        clock_t begin = clock();
        search_LSH(&nnPoint, &distanceLSH, numOfHashTables, hashers, queryPoint, hts,metric);
        clock_t end = clock();
        meanSearchLSH += (end-begin);
        begin = clock();
        search_BruteForce(&nnPoint, &distanceBF, data, queryPoint,metric);
        end = clock();
        meanSearchBF += (end-begin);
        double AF;
        if ((AF = distanceLSH/distanceBF) > maxAF) 
            maxAF = AF;
        if (distanceLSH) {//compute only if > 0
            averageAF += distanceLSH/distanceBF;
            averageAFCount++;
        }
    }
    cout << "meanTimeSearchLSH " << meanSearchLSH/querySize << " meanTimeSearchBF " << meanSearchBF/querySize << " and maxAF = " << maxAF << " and averageAF " << averageAF/averageAFCount << endl;
}
