#ifndef ALGORITHMS_PROJECT_LSH_H
#define ALGORITHMS_PROJECT_LSH_H
#include "Dataset.h"
#include "HashTableStruct.h"

class LSH {
private:
    string inputFilename; bool inputFileGiven = false;
    string queryFilename; bool queryFileGiven = false;
    string outputFilename; bool outputFileGiven = false;
    int numOfFunctions = 4;
    int numOfHashTables = 5;

    Dataset* data;
    QueryDataset* queryData;
    HashTableStruct * tables;

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

    void setHashTableStruct(HashTableStruct *ht);

    auto getHashTableStruct() { return tables;}

    virtual void poly(){};
};

#endif //ALGORITHMS_PROJECT_LSH_H
