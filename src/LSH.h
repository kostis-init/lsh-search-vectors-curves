#ifndef ALGORITHMS_PROJECT_LSH_H
#define ALGORITHMS_PROJECT_LSH_H
#include "Dataset.h"
#include "HashTableStruct.h"

template <typename T>
class LSH {
private:
    string inputFilename; bool inputFileGiven = false;
    string queryFilename; bool queryFileGiven = false;
    string outputFilename; bool outputFileGiven = false;
    int numOfFunctions = 4;
    int numOfHashTables = 5;

    Dataset* data;
    QueryDataset* queryData;
    HashTableStruct<T> * tables;

public:

    const string &getInputFilename() const;

    void setInputFilename(const string &inputFilename);

    bool isInputFileGiven() const;

    const string &getQueryFilename() const;

    void setQueryFilename(const string &queryFilename);

    bool isQueryFileGiven() const;

    const string &getOutputFilename() const;

    void setOutputFilename(const string &outputFilename);

    bool isOutputFileGiven() const;

    int getNumOfFunctions() const;

    void setNumOfFunctions(int numOfFunctions);

    int getNumOfHashTables() const;

    void setNumOfHashTables(int numOfHashTables);

    Dataset *getDataset() const;

    void setData(Dataset *data);

    QueryDataset *getQueryData() const;

    void setQueryData(QueryDataset *queryData);

    void setHashTableStruct(HashTableStruct<T> *ht);

    auto getHashTableStruct() { return tables;}
};

template <typename T>
const string &LSH<T>::getInputFilename() const {
    return inputFilename;
}
template <typename T>
void LSH<T>::setInputFilename(const string &inputFilename) {
    inputFileGiven = true;
    this->inputFilename = inputFilename;
}
template <typename T>
bool LSH<T>::isInputFileGiven() const {
    return inputFileGiven;
}
template <typename T>
const string &LSH<T>::getQueryFilename() const {
    return queryFilename;
}
template <typename T>
void LSH<T>::setQueryFilename(const string &queryFilename) {
    queryFileGiven = true;
    this->queryFilename = queryFilename;
}
template <typename T>
bool LSH<T>::isQueryFileGiven() const {
    return queryFileGiven;
}
template <typename T>
const string &LSH<T>::getOutputFilename() const {
    return outputFilename;
}
template <typename T>
void LSH<T>::setOutputFilename(const string &outputFilename) {
    outputFileGiven = true;
    this->outputFilename = outputFilename;
}
template <typename T>
bool LSH<T>::isOutputFileGiven() const {
    return outputFileGiven;
}
template <typename T>
int LSH<T>::getNumOfFunctions() const {
    return numOfFunctions;
}
template <typename T>
void LSH<T>::setNumOfFunctions(int numOfFunctions) {
    this->numOfFunctions = numOfFunctions;
}
template <typename T>
int LSH<T>::getNumOfHashTables() const {
    return numOfHashTables;
}
template <typename T>
void LSH<T>::setNumOfHashTables(int numOfHashTables) {
    this->numOfHashTables = numOfHashTables;
}
template <typename T>
Dataset *LSH<T>::getDataset() const {
    return data;
}
template <typename T>
void LSH<T>::setData(Dataset *data) {
    this->data = data;
}
template <typename T>
QueryDataset *LSH<T>::getQueryData() const {
    return queryData;
}
template <typename T>
void LSH<T>::setQueryData(QueryDataset *queryData) {
    this->queryData = queryData;
}

template <typename T>
void LSH<T>::setHashTableStruct(HashTableStruct<T> *ht) {
    tables = ht;
}

#endif //ALGORITHMS_PROJECT_LSH_H
