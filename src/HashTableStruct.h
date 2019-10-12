#ifndef ALGORITHMS_PROJECT_HASHTABLESTRUCT_H
#define ALGORITHMS_PROJECT_HASHTABLESTRUCT_H
#include <vector>
#include <iostream>
#include <unordered_set>
#include "Object.h"
#include "Point.h"
#include "hasher.h"

using namespace std;

//------------------------------
template<typename T>
class HashTableStruct {
private:
    int numOfHTs;
    //set hasher!!!
    unordered_set<Object *, T> * hashTables;
public:
    HashTableStruct(int numOfHTs);
    ~HashTableStruct();
    int getNumOfHTs() {return numOfHTs;}
    auto getAllHashTables() {return hashTables;}
    auto getHashTable(int index) {return hashTables[index];}
    void addToAllHashTables(Object *obj);
    void addToHashTable(int ht_index, Object *obj);
    void test_print_hashtable(int,Object *);

};

template<typename T>
HashTableStruct<T>::HashTableStruct(int numOfHTs) {
    this->numOfHTs = numOfHTs;
    this->hashTables = new unordered_set<Object *, T>[numOfHTs];
}
template<typename T>
HashTableStruct<T>::~HashTableStruct() {
    delete[] hashTables;
}

template<typename T>
void HashTableStruct<T>::addToAllHashTables(Object *obj) {
    for (int i = 0; i < numOfHTs; ++i) {
        this->hashTables[i].insert(obj);
    }
}

template<typename T>
void HashTableStruct<T>::addToHashTable(int ht_index, Object * obj) {
    this->hashTables[ht_index].insert(obj);
}

template<typename T>
void HashTableStruct<T>::test_print_hashtable(int ht_index, Object * obj) {
    auto hts = hashTables;
    for (int i = 0; i < numOfHTs; i++) {
        auto fn = hts[i].hash_function();
        cout << "\nHASH TABLE " << i + 1 << endl;
        for(auto entry : hts[i]){
            cout << "Item Id: " << entry->getId();
            cout << ",\thash func: " << fn(entry);
            cout << ",\tbucket #" << hts[i].bucket(entry);
            cout << ",\tbucket count: " << hts[i].bucket_count();
            cout << endl;
        }
    }
}

//struct HashPoint {
//    size_t operator() (Object *obj) const {
//        //auto h = new PointHasher(5,5);
//        //return h->hash(obj);
//        return obj->getId().length();
//    }
//};

#endif //ALGORITHMS_PROJECT_HASHTABLESTRUCT_H
