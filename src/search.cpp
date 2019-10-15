#include "search.h"
#include "distance.h"
#include <limits>

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
        Point* nnPoint;
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
