#include <vector>
#include "HashTableStruct.h"

HashTableStruct::HashTableStruct(int numOfHTs, size_t sz) {
    //hashers = new [numOfHTs];
    this->numOfHTs = numOfHTs;
    this->size = sz/8;
    this->hashTables = new unordered_map<int, vector<Object *>>[numOfHTs];
}
HashTableStruct::~HashTableStruct() {
    delete[] hashTables;
}

void HashTableStruct::addToAllHashTables(Object *obj) {
    counter++ ;
    for (int i = 0; i < numOfHTs; ++i) {
        size_t hash = (*hashers.at(i))(obj);
        auto item = hashTables[i].find(hash);
        if(item != hashTables[i].end()){ //found
            hashTables[i].at(hash).push_back(obj);
        }
        else{ //not found
            vector<Object *> arg;
            arg.push_back(obj);
            hashTables[i].insert(make_pair(hash, arg));
        }
    }
    if(counter%5000 == 0)
        cout << obj->getId() << endl;
}

void HashTableStruct::test_print_hashtable() {
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

CurveHashTableStruct::CurveHashTableStruct(int numOfHTs,size_t sz,int ampSize,int numDimension,int min,int max,int pointHasherWindow) :HashTableStruct(numOfHTs,sz) {
   CurveHasher **h; 
   h = new CurveHasher*[numOfHTs];
   for (int i =0; i < numOfHTs; i++) 
      h[i] = new CurveHasher(numDimension,ampSize,min,max,pointHasherWindow);
    hashers = vector<Hasher *>(h,h+numOfHTs);
}

PointHashTableStruct::PointHashTableStruct(int numOfHTs,size_t sz,int ampSize,int numDimension,int window) : HashTableStruct(numOfHTs,sz) {
   PointHasher **h; 
   h = new PointHasher*[numOfHTs];
   for (int i =0; i < numOfHTs; i++)
      h[i] = new PointHasher(ampSize,numDimension,window);
    hashers = vector<Hasher *> (h,h+numOfHTs);

}