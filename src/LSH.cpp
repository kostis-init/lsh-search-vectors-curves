#include "LSH.h"

const string &LSH::getInputFilename() const {
    return inputFilename;
}

void LSH::setInputFilename(const string &inputFilename) {
    LSH::inputFilename = inputFilename;
}

bool LSH::isInputFileGiven() const {
    return inputFileGiven;
}

void LSH::setInputFileGiven(bool inputFileGiven) {
    LSH::inputFileGiven = inputFileGiven;
}

const string &LSH::getQueryFilename() const {
    return queryFilename;
}

void LSH::setQueryFilename(const string &queryFilename) {
    LSH::queryFilename = queryFilename;
}

bool LSH::isQueryFileGiven() const {
    return queryFileGiven;
}

void LSH::setQueryFileGiven(bool queryFileGiven) {
    LSH::queryFileGiven = queryFileGiven;
}

const string &LSH::getOutputFilename() const {
    return outputFilename;
}

void LSH::setOutputFilename(const string &outputFilename) {
    LSH::outputFilename = outputFilename;
}

bool LSH::isOutputFileGiven() const {
    return outputFileGiven;
}

void LSH::setOutputFileGiven(bool outputFileGiven) {
    LSH::outputFileGiven = outputFileGiven;
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
