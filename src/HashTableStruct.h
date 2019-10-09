#ifndef ALGORITHMS_PROJECT_HASHTABLESTRUCT_H
#define ALGORITHMS_PROJECT_HASHTABLESTRUCT_H
#include <vector>
#include <unordered_set>
#include "Object.h"
#include "Point.h"
#include "hasher.h"

using namespace std;

class HashTableStruct {
private:

    int numOfHTs;
    //set hasher!!!
    unordered_set<Object *, PointHasher> * hashTables;

public:

    HashTableStruct(int numOfHTs);
    ~HashTableStruct();

    int getNumOfHTs() {return numOfHTs;}
    auto getAllHashTables() {return hashTables;}
    auto getHashTable(int index) {return hashTables[index];}

    void addToAllHashTables(Object *obj);
    void addToHashTable(int ht_index, Object *obj);

};


//struct HashPoint {
//    size_t operator() (Object *obj) const {
//        //auto h = new PointHasher(5,5);
//        //return h->hash(obj);
//        return obj->getId().length();
//    }
//};

#endif //ALGORITHMS_PROJECT_HASHTABLESTRUCT_H
