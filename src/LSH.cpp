#include "LSH.h"

const string &LSH::getInputFilename() const {
    return inputFilename;
}

void LSH::setInputFilename(const string &inputFilename) {
    LSH::inputFileGiven = true;
    LSH::inputFilename = inputFilename;
}

bool LSH::isInputFileGiven() const {
    return inputFileGiven;
}

const string &LSH::getQueryFilename() const {
    return queryFilename;
}

void LSH::setQueryFilename(const string &queryFilename) {
    LSH::queryFileGiven = true;
    LSH::queryFilename = queryFilename;
}

bool LSH::isQueryFileGiven() const {
    return queryFileGiven;
}

const string &LSH::getOutputFilename() const {
    return outputFilename;
}

void LSH::setOutputFilename(const string &outputFilename) {
    LSH::outputFileGiven = true;
    LSH::outputFilename = outputFilename;
}

bool LSH::isOutputFileGiven() const {
    return outputFileGiven;
}

int LSH::getNumOfFunctions() const {
    return numOfFunctions;
}

void LSH::setNumOfFunctions(int numOfFunctions) {
    LSH::numOfFunctions = numOfFunctions;
}

int LSH::getNumOfHashTables() const {
    return numOfHashTables;
}

void LSH::setNumOfHashTables(int numOfHashTables) {
    LSH::numOfHashTables = numOfHashTables;
}

DatasetPoints *LSH::getData() const {
    return data;
}

void LSH::setData(DatasetPoints *data) {
    LSH::data = data;
}

QueryDatasetPoints *LSH::getQueryData() const {
    return queryData;
}

void LSH::setQueryData(QueryDatasetPoints *queryData) {
    LSH::queryData = queryData;
}
