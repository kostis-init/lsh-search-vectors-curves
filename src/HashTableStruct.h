#ifndef ALGORITHMS_PROJECT_HASHTABLESTRUCT_H
#define ALGORITHMS_PROJECT_HASHTABLESTRUCT_H
#include <vector>
#include <unordered_map>
#include "Object.h"

using namespace std;

class HashTableStruct {
private:

    int numOfHTs;
    unordered_map<int, vector<Object *>> * hashTables;

public:

    HashTableStruct(int numOfHTs);
    ~HashTableStruct();

    auto getAllHashTables();
    auto getHashTable(int index);

};



#endif //ALGORITHMS_PROJECT_HASHTABLESTRUCT_H
