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

template<typename T>
class HashTableStruct {
private:
    //for debug
    int counter = 0;
    int numOfHTs;
    int size; //size of every hash table;
    T* hashers;
    unordered_map<int, vector<Object *>> * hashTables;
public:
    HashTableStruct(int numOfHTs, int sz);
    ~HashTableStruct();
    int getNumOfHTs() {return numOfHTs;}
    auto getAllHashTables() {return hashTables;}
    auto getHashTable(int index) {return hashTables[index];}
    void addToAllHashTables(Object *obj);
    void test_print_hashtable();

};

template<typename T>
HashTableStruct<T>::HashTableStruct(int numOfHTs, int sz) {
    hashers = new T[numOfHTs];
    this->numOfHTs = numOfHTs;
    this->size = sz/8;
    this->hashTables = new unordered_map<int, vector<Object *>>[numOfHTs];
}
template<typename T>
HashTableStruct<T>::~HashTableStruct() {
    delete[] hashTables;
}

template<typename T>
void HashTableStruct<T>::addToAllHashTables(Object *obj) {
    counter++ ;
    for (int i = 0; i < numOfHTs; ++i) {
        size_t hash = hashers[i](obj);
        auto item = hashTables[i].find(hash);
        if(item != hashTables[i].end()){ //found
            hashTables[i].at(hashers[i](obj)).push_back(obj);
        }
        else{ //not found
            vector<Object *> arg;
            arg.push_back(obj);
            hashTables[i].insert(make_pair(hash, arg));
        }
    }
    if(counter%1000 == 0)
        cout << obj->getId() << endl;
}

template<typename T>
void HashTableStruct<T>::test_print_hashtable() {
    auto hts = hashTables;
    for (int i = 0; i < numOfHTs; i++) {
        cout << "\nHASH TABLE " << i + 1 << endl;
        for(auto const& x : hts[i]){
            cout<<"bucket #"<< x.first << endl;
            for(auto el : x.second){
                cout << el->getId() << endl;
            }
        }
    }
}

#endif //ALGORITHMS_PROJECT_HASHTABLESTRUCT_H
