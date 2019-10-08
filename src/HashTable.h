#ifndef ALGORITHMS_PROJECT_HASHTABLE_H
#define ALGORITHMS_PROJECT_HASHTABLE_H

#include <list>
#include <vector>
#include "Object.h"

class HashTable {
private:
    int size;
    std::vector<std::list<Object*>> buckets;
public:
    HashTable(int size);
    ~HashTable();
};

class HashTableList {
private:
    std::list<HashTable*> hashTableList;
public:
    HashTableList(int numOfHTs, int sizeOfHTs);
    ~HashTableList();

    std::list<HashTable*> getList() {return hashTableList;}
};



#endif //ALGORITHMS_PROJECT_HASHTABLE_H
