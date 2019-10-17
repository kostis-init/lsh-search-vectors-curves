#ifndef ALGORITHMS_PROJECT_HASHTABLESTRUCT_H
#define ALGORITHMS_PROJECT_HASHTABLESTRUCT_H
#include <vector>
#include <iostream>
#include <unordered_map>
#include <list>
#include "Object.h"
#include "Point.h"
#include "hasher.h"

using namespace std;

class HashTableStruct {
private:
    //for debug
    int counter = 0;
    int numOfHTs;
    size_t size; //size of every hash table;
    unordered_map<int, vector<Object *>> * hashTables;
protected:
    //Hasher* hashers;
    vector<Hasher *> hashers;
public:
    HashTableStruct(int numOfHTs, size_t sz);
    ~HashTableStruct();

    int getNumOfHTs() {return numOfHTs;}
    auto getAllHashTables() {return hashTables;}
    auto getHashTable(int index) {return hashTables[index];}
    auto getHashers() {return hashers;}

    void addToAllHashTables(Object *obj);
    void test_print_hashtable();

};

class PointHashTableStruct : public HashTableStruct {
    public:
        PointHashTableStruct(int numOfHTs,size_t sz,int ampSize,int numDimension,int window);
};

class CurveHashTableStruct : public HashTableStruct {
    public:
        CurveHashTableStruct(int numOfHTs,size_t sz,int ampSize,int numDimension,int min,int max,int pointHasherWindow);
};
#endif //ALGORITHMS_PROJECT_HASHTABLESTRUCT_H
