#ifndef ALGORITHMS_PROJECT_LSH_H
#define ALGORITHMS_PROJECT_LSH_H
#include "Dataset.h"

class LSH {
private:
    string inputFilename; bool inputFileGiven = false;
    string queryFilename; bool queryFileGiven = false;
    string outputFilename; bool outputFileGiven = false;
    int numOfFunctions = 4;
    int numOfHashTables = 5;

    DatasetPoints* data;
public:
    const string &getInputFilename() const;

    void setInputFilename(const string &inputFilename);

    bool isInputFileGiven() const;

    void setInputFileGiven(bool inputFileGiven);

    const string &getQueryFilename() const;

    void setQueryFilename(const string &queryFilename);

    bool isQueryFileGiven() const;

    void setQueryFileGiven(bool queryFileGiven);

    const string &getOutputFilename() const;

    void setOutputFilename(const string &outputFilename);

    bool isOutputFileGiven() const;

    void setOutputFileGiven(bool outputFileGiven);

    int getNumOfFunctions() const;

    void setNumOfFunctions(int numOfFunctions);

    int getNumOfHashTables() const;

    void setNumOfHashTables(int numOfHashTables);

    DatasetPoints *getData() const;

    void setData(DatasetPoints *data);
};


#endif //ALGORITHMS_PROJECT_LSH_H
