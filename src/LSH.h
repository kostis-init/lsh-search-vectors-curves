#ifndef ALGORITHMS_PROJECT_LSH_H
#define ALGORITHMS_PROJECT_LSH_H
#include "Dataset.h"
#include "HashTableStruct.h"
#include "distance.h"

class LSH {
private:

    string inputFilename; bool inputFileGiven = false;
    string queryFilename; bool queryFileGiven = false;
    string outputFilename; bool outputFileGiven = false;

    Dataset* data;
    QueryDataset* queryData;
    HashTableStruct * tables;
    DistanceMetric *distMetric;
    //L_grid for Curves - L for Points
    int numOfFunctions = 0;
    //k_vec for Curves - k for Points
    int numOfHashTables = 0;

public:
    LSH(DistanceMetric *metric) {
        distMetric = metric;
    }
    DistanceMetric *getMetric() { return distMetric;}
    const string &getInputFilename() const {return inputFilename;}
    const string &getQueryFilename() const {return queryFilename;}
    const string &getOutputFilename() const {return outputFilename;}
    bool isInputFileGiven() const {return inputFileGiven;}
    bool isQueryFileGiven() const {return queryFileGiven;}
    bool isOutputFileGiven() const {return outputFileGiven;}
    Dataset *getDataset() const {return data;}
    QueryDataset *getQueryData() const {return queryData;}
    void setInputFilename(const string &inputFilename){
        inputFileGiven = true;
        this->inputFilename = inputFilename;
    }

    void setQueryFilename(const string &queryFilename){
        queryFileGiven = true;
        this->queryFilename = queryFilename;
    }

    void setOutputFilename(const string &outputFilename){
        outputFileGiven = true;
        this->outputFilename = outputFilename;
    }

    void setData(Dataset *data) {
        this->data = data;
    }

    void setQueryData(QueryDataset *queryData) {
        this->queryData = queryData;
    }

    int getNumOfFunctions() const {return numOfFunctions;}
    int getNumOfHashTables() const {return numOfHashTables;}
    auto getHashTableStruct() {return tables;}

    void setNumOfFunctions(int numOfFunctions){
        this->numOfFunctions = numOfFunctions;
    }

    void setNumOfHashTables(int numOfHashTables){
        this->numOfHashTables = numOfHashTables;
    }

    void setHashTableStruct(HashTableStruct *ht) {
        tables = ht;
    }

};

#endif //ALGORITHMS_PROJECT_LSH_H
