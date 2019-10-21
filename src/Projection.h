#ifndef ALGORITHMS_PROJECT_PROJECTION_H
#define ALGORITHMS_PROJECT_PROJECTION_H

#include <iostream>
#include <tuple>
#include <vector>
#include <string.h>
#include "RelevantTraversals.h"
#include "Dataset.h"
#include "GenericAlgorithm.h"

using namespace std;

class Projection : public GenericAlgorithm{
private:
    vector<vector<RelevantTraversals *>> traversalsMatrix;
    //G matrix
public:

    auto getTraversalsMatrix(){ return traversalsMatrix;}

    void buildTraversalsMatrix(int size){
        for (int i = 0; i < size; ++i) {
            vector<RelevantTraversals *> line;
            // Create traversals for two curves with lengths i + 1, j + 1 respectively.
            // Save memory by starting j from i, as i,j and j,i have the same traversals
            for (int j = i; j < size; ++j)
                line.push_back(new RelevantTraversals(i + 1, j + 1));
            traversalsMatrix.push_back(line);
        }
    }


};


#endif //ALGORITHMS_PROJECT_PROJECTION_H
