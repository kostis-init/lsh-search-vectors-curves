#include "search.h"
#include "distance.h"
#include <limits>
#include <bitset>
#include <set>

void search_Cube_vs_BruteForce(Cube* cube){
    int querySize = cube->getLsh()->getQueryData()->getSize();
    auto queryData = cube->getLsh()->getQueryData()->getData();
    double queryRadius = cube->getLsh()->getQueryData()->getRadius();

    for (int i = 0; i < querySize; ++i) {
        Object* queryObject = queryData.at(i);
        cout << "Query: " << queryObject->getId() << endl;
        Object* nearestNeighbor = nullptr;
        double distance;
        set<Object*> radiusNeighbors;

        //Cube
        cout << "Cube" << endl;

        clock_t begin = clock();
        search_Cube(&nearestNeighbor, &distance, queryObject, cube, radiusNeighbors, queryRadius);
        clock_t end = clock();

        if(nearestNeighbor == nullptr){
            cout << "Nearest neighbor: Not Found" << endl;
        } else {
            cout << "Nearest neighbor Cube: " << nearestNeighbor->getId() << endl;
            cout << "distance Cube: " << distance << endl;
            cout << "time Cube: " << end - begin << endl;
        }

        //Brute Force
        cout << "Brute Force" << endl;

        begin = clock();
        search_BruteForce(&nearestNeighbor, &distance, cube->getLsh()->getDataset()->getData(), queryObject, cube->getLsh()->getMetric());
        end = clock();

        cout << "Nearest neighbor Brute Force: " << nearestNeighbor->getId() << endl;
        cout << "distance Brute Force: " << distance << endl;
        cout << "time Brute Force: " << end - begin << endl;
        cout << "R-near neighbors:" << endl;
        for(auto n : radiusNeighbors){
            cout << n->getId() << endl;
        }
        cout << endl << endl;

    }
}

void search_Cube(Object **nearestNeighbor, double *distance, Object* queryObject, Cube* cube, set<Object*>& radiusNeighbors, double radius) {
    random_device randomDevice;
    mt19937 mt(randomDevice());
    uniform_int_distribution<unsigned int> dist(0,1);

    auto binaryMaps = cube->getBinaryMaps();
    auto hashers = cube->getLsh()->getHashTableStruct()->getHashers();
    auto vertices = cube->getVertices();

    size_t index = 0;
    //construct index
    for (int i = 0; i < cube->getDimension(); ++i) {
        size_t hash = (*hashers.at(i))(queryObject);
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
    auto metric = cube->getLsh()->getMetric();
    *nearestNeighbor = nullptr;
    *distance = numeric_limits<double>::max();

    //search on index (vertex), starting from current
    // and then go to vertices of hamming distance 1 (or 2, if 1 is exhausted)
    while(limit > 0 && probes >= 0){
        for(auto candidate : vertices[probe_index]){
            double cur_dist = metric->dist(queryObject, candidate);
            if(cur_dist <= radius)
                radiusNeighbors.insert(candidate);
            if(cur_dist < *distance){
                *distance = cur_dist;
                *nearestNeighbor = candidate;
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

void search_LSH_vs_BruteForce(LSH* lsh) {
    int querySize = lsh->getQueryData()->getSize();
    auto queryData = lsh->getQueryData()->getData();
    double queryRadius = lsh->getQueryData()->getRadius();

    for (int i = 0; i < querySize; ++i) {
        Object* queryObject = queryData.at(i);
        cout << "Query: " << queryObject->getId() << endl;
        Object* nearestNeighbor = nullptr;
        double distance;
        set<Object *> radiusNeighbors;

        //LSH
        cout << "LSH" << endl;

        clock_t begin = clock();
        search_LSH(&nearestNeighbor, &distance, queryObject, lsh, radiusNeighbors, queryRadius);
        clock_t end = clock();

        if(nearestNeighbor == nullptr){
            cout << "Nearest neighbor: Not Found" << endl;
        } else {
            cout << "Nearest neighbor LSH: " << nearestNeighbor->getId() << endl;
            cout << "distance LSH: " << distance << endl;
            cout << "time LSH: " << end - begin << endl;
        }

        //Brute Force
        cout << "Brute Force" << endl;

        begin = clock();
        search_BruteForce(&nearestNeighbor, &distance, lsh->getDataset()->getData(), queryObject, lsh->getMetric());
        end = clock();

        cout << "Nearest neighbor Brute Force: " << nearestNeighbor->getId() << endl;
        cout << "distance Brute Force: " << distance << endl;
        cout << "time Brute Force: " << end - begin << endl;
        cout << "R-near neighbors:" << endl;
        for(auto n : radiusNeighbors){
            cout << n->getId() << endl;
        }
        cout << endl << endl;
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

void search_LSH(Object **nearestNeighbor, double *distance, Object *queryObject, LSH* lsh, set<Object*>& radiusNeighbors, double radius) {
    *nearestNeighbor = nullptr;
    *distance = numeric_limits<double>::max();
    bool found = false;
    //int threshold = 50 * lsh->getNumOfHashTables();
    int threshold = 10 * lsh->getNumOfHashTables();
    int thresholdCount = 0;
    auto hashers = lsh->getHashTableStruct()->getHashers();
    auto hts = lsh->getHashTableStruct()->getAllHashTables();
    for (int j = 0; j < lsh->getNumOfHashTables(); ++j) {
        size_t hash = (*hashers.at(j))(queryObject);
        if(hts[j].find(hash) == hts[j].end()) //empty bucket
            continue;
        auto points = hts[j].at(hash);
        thresholdCount = 0;
        for(auto candidate : points){
            if (thresholdCount > threshold)
                break;
            double cur_dist = lsh->getMetric()->dist(queryObject, candidate);
            if(cur_dist <= radius)
                radiusNeighbors.insert(candidate);
            if(cur_dist < *distance){
                found = true;
                *distance = cur_dist;
                *nearestNeighbor = candidate;
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
    int querySize = lsh->getQueryData()->getSize();
    auto queryData = lsh->getQueryData()->getData();
    double queryRadius = lsh->getQueryData()->getRadius();

    clock_t meanSearchLSH = 0;
    clock_t meanSearchBF = 0;
    double maxAF = numeric_limits<double>::min();
    double averageAF = 0;
    int averageAFCount = 0;
    int notFound = 0;

    for (int i = 0; i < querySize; ++i) {
        Object* queryPoint = (Point*)queryData.at(i);
        Object* nnPoint;
        set<Object*> radiusNeighbors;
        double distanceLSH;
        double distanceBF;
        clock_t begin = clock();
        search_LSH(&nnPoint, &distanceLSH, queryPoint, lsh, radiusNeighbors, queryRadius);
        clock_t end = clock();
        meanSearchLSH += (end-begin);
        begin = clock();
        search_BruteForce(&nnPoint, &distanceBF, lsh->getDataset()->getData(), queryPoint, lsh->getMetric());
        end = clock();
        meanSearchBF += (end-begin);
        double AF;
        if ((AF = distanceLSH/distanceBF) > maxAF) 
            maxAF = AF;
        if (distanceLSH > 0) {//compute only if > 0
            averageAF += distanceLSH/distanceBF;
            averageAFCount++;
        } else
            notFound++;
        cout << " i : " << i << " AF " << AF << endl;
    }
    cout << "meanTimeSearchLSH " << meanSearchLSH/querySize << " meanTimeSearchBF " << meanSearchBF/querySize
        << " and maxAF = " << maxAF << " and averageAF " << averageAF/averageAFCount << " and not found: " << notFound << endl;
}

void DoQueries(Cube *cube) {
    int querySize = cube->getLsh()->getQueryData()->getSize();
    auto queryData = cube->getLsh()->getQueryData()->getData();
    double queryRadius = cube->getLsh()->getQueryData()->getRadius();
    clock_t meanSearchCube = 0;
    clock_t meanSearchBF = 0;
    double maxAF = numeric_limits<double>::min();
    double averageAF = 0;
    int averageAFCount = 0;
    int notFound = 0;
    for (int i = 0; i < querySize; ++i) {
        Object* queryPoint = (Point*)queryData.at(i);
        Object* nnPoint;
        set<Object*> radiusNeighbors;
        double distanceCube;
        double distanceBF;
        clock_t begin = clock();
        search_Cube(&nnPoint, &distanceCube, queryPoint, cube, radiusNeighbors, queryRadius);
        clock_t end = clock();
        meanSearchCube += (end-begin);
        begin = clock();
        search_BruteForce(&nnPoint, &distanceBF, cube->getLsh()->getDataset()->getData(), queryPoint, cube->getLsh()->getMetric());
        end = clock();
        meanSearchBF += (end-begin);
        double AF;
        if ((AF = distanceCube / distanceBF) > maxAF)
            maxAF = AF;
        if (distanceCube > 0) {//compute only if > 0
            averageAF += distanceCube / distanceBF;
            averageAFCount++;
        }else
            notFound++;
    }
    cout << "meanTimeSearchCube " << meanSearchCube/querySize << " meanTimeSearchBF " << meanSearchBF/querySize
        << " and maxAF = " << maxAF << " and averageAF " << averageAF/averageAFCount << " and not found: " << notFound << endl;
}

void search_LSH_Projection(Object **nearestNeighbor, double *distance, Object *queryObject, Projection* projection){
    Curve* queryCurve = dynamic_cast<Curve*>(queryObject);
    *nearestNeighbor = nullptr;
    *distance = numeric_limits<double>::max();
    bool found = false;
    int threshold = 20 * projection->getAnn()->getNumOfHashTables();
    int thresholdCount = 0;
    for (int i = 0; i < projection->getTraversalsMatrix().size(); ++i) {
        if(fabs(i - (queryCurve->getPoints().size()-1)) > 4){
            continue;
        }
        auto traversals = projection->getTraversalsMatrix().at(i).at(queryCurve->getPoints().size()-1);
        for (int j = 0; j < traversals->getTraversals().size(); ++j) {
            LSH* lsh = dynamic_cast<LSH*>(traversals->getAnnStructs().at(j));

            auto hashers = lsh->getHashTableStruct()->getHashers();
            auto hts = lsh->getHashTableStruct()->getAllHashTables();
            thresholdCount = 0;
            for (int j = 0; j < lsh->getNumOfHashTables(); ++j) {
                if (thresholdCount > threshold)
                    break;
                size_t hash = (*hashers.at(j))(queryObject, false);
                if(hts[j].find(hash) == hts[j].end()) //empty bucket
                    continue;
                auto points = hts[j].at(hash);
                for(auto candidate : points){
                    if (thresholdCount > threshold)
                        break;
                    double cur_dist = lsh->getMetric()->dist(queryObject, candidate);
                    if(cur_dist < *distance){
                        found = true;
                        *distance = cur_dist;
                        *nearestNeighbor = candidate;
                    }
                    thresholdCount++;
                }
            }

        }
    }

    //if we fall in empty backet for all htables
    //set dist to zero (otherwise AF calculation is useless)
    if (!found)
        *distance = 0.0;
}

void search_LSH_vs_BruteForce_Projection(Projection* projection){
    int querySize = projection->getQueryData()->getSize();
    auto queryData = projection->getQueryData()->getData();

    for (int i = 0; i < querySize; ++i) {
        Object* queryObject = queryData.at(i);
        cout << "Query: " << queryObject->getId() << endl;
        Object* nearestNeighbor = nullptr;
        double distance;

        //LSH
        cout << "LSH" << endl;

        clock_t begin = clock();
        search_LSH_Projection(&nearestNeighbor, &distance, queryObject, projection);
        clock_t end = clock();

        if(nearestNeighbor == nullptr){
            cout << "Nearest neighbor: Not Found" << endl;
        } else {
            cout << "Nearest neighbor LSH: " << nearestNeighbor->getId() << endl;
            cout << "distance LSH: " << distance << endl;
            cout << "time LSH: " << end - begin << endl;
        }

        //Brute Force
        cout << "Brute Force" << endl;

        begin = clock();
        search_BruteForce(&nearestNeighbor, &distance, projection->getDataset()->getData(), queryObject, new DTW);
        end = clock();

        cout << "Nearest neighbor Brute Force: " << nearestNeighbor->getId() << endl;
        cout << "distance Brute Force: " << distance << endl;
        cout << "time Brute Force: " << end - begin << endl << endl;
    }
}

void DoQueries(Projection* projection){
    int querySize = projection->getQueryData()->getSize();
    auto queryData = projection->getQueryData()->getData();

    clock_t meanSearchLSH = 0;
    clock_t meanSearchBF = 0;
    double maxAF = numeric_limits<double>::min();
    double averageAF = 0;
    int averageAFCount = 0;
    int notFound = 0;

    for (int i = 0; i < querySize; ++i) {
        Object* queryObject = queryData.at(i);
        Object* nnPoint;
        double distanceLSH;
        double distanceBF;
        clock_t begin = clock();
        search_LSH_Projection(&nnPoint, &distanceLSH, queryObject, projection);
        clock_t end = clock();
        meanSearchLSH += (end-begin);
        begin = clock();
        search_BruteForce(&nnPoint, &distanceBF, projection->getDataset()->getData(), queryObject, new DTW);
        end = clock();
        meanSearchBF += (end-begin);
        double AF;
        if ((AF = distanceLSH/distanceBF) > maxAF)
            maxAF = AF;
        if (distanceLSH > 0) {//compute only if > 0
            averageAF += distanceLSH/distanceBF;
            averageAFCount++;
        } else
            notFound++;
        cout << " i : " << i << " AF " << AF << endl;
    }
    cout << "meanTimeSearchLSH " << meanSearchLSH/querySize << " meanTimeSearchBF " << meanSearchBF/querySize << " and maxAF = "
        << maxAF << " and averageAF " << averageAF/averageAFCount << " and not found: " << notFound << endl;
}