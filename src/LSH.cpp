#include "LSH.h"

const string &LSH::getInputFilename() const {
    return inputFilename;
}
void LSH::setInputFilename(const string &inputFilename) {
    inputFileGiven = true;
    this->inputFilename = inputFilename;
}
bool LSH::isInputFileGiven() const {
    return inputFileGiven;
}
const string &LSH::getQueryFilename() const {
    return queryFilename;
}
void LSH::setQueryFilename(const string &queryFilename) {
    queryFileGiven = true;
    this->queryFilename = queryFilename;
}
bool LSH::isQueryFileGiven() const {
    return queryFileGiven;
}
const string &LSH::getOutputFilename() const {
    return outputFilename;
}
void LSH::setOutputFilename(const string &outputFilename) {
    outputFileGiven = true;
    this->outputFilename = outputFilename;
}
bool LSH::isOutputFileGiven() const {
    return outputFileGiven;
}
int LSH::getNumOfFunctions() const {
    return numOfFunctions;
}
void LSH::setNumOfFunctions(int numOfFunctions) {
    this->numOfFunctions = numOfFunctions;
}
int LSH::getNumOfHashTables() const {
    return numOfHashTables;
}
void LSH::setNumOfHashTables(int numOfHashTables) {
    this->numOfHashTables = numOfHashTables;
}
Dataset *LSH::getDataset() const {
    return data;
}
void LSH::setData(Dataset *data) {
    this->data = data;
}
QueryDataset *LSH::getQueryData() const {
    return queryData;
}
void LSH::setQueryData(QueryDataset *queryData) {
    this->queryData = queryData;
}

void LSH::setHashTableStruct(HashTableStruct *ht) {
    tables = ht;
}
