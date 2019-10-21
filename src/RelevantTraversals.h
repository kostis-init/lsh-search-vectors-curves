#ifndef ALGORITHMS_PROJECT_RELEVANTTRAVERSALS_H
#define ALGORITHMS_PROJECT_RELEVANTTRAVERSALS_H

#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

class RelevantTraversals {
private:
    int length1, length2;
    vector<vector<tuple<int, int>>> traversals;

    /**
     * This matrix is used as a helper to create
     * relevant traversals. The cells that are
     * close to the diagonal, are set to true.
     */
    bool **traversalsMatrix;

    void createTraversalsMatrix();
    void deleteTraversalsMatrix();

    void createRelevantTraversals();
    void constructTraversalsRecursively(vector<tuple<int, int>> traversal, int i, int j);

    void printTraversalsMatrix();
    void printRelevantTraversals();
public:

    RelevantTraversals(int length1, int length2);

};

#endif //ALGORITHMS_PROJECT_RELEVANTTRAVERSALS_H
