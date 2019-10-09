#ifndef HASHER_H
#define HASHER_H 
#include "Object.h"

//#define GRID_POOL 50
#define WINDOW_SIZE 100


class Hasher {
    public:
        virtual int Hash(Object *obj) = 0;
};

//Create an instance per LSHHashtable.
//Call hash(Object*) and the return value will be
//the index of the bucket that Object should be stored.
class PointHasher : public Hasher {
    private:
        const int window = WINDOW_SIZE;
        //size depends on amplification size -evaluated at constructor?
        double **gridPool;
        int gridPoolSize;
        int amplificationSize;
        int numDimension;
        int * selectedGrids;
        void generateGrids();
    public:
        //amplificationSize=k , numDimension =d as described in slides.
        PointHasher(int amplificationSize,int numDimension);
        ~PointHasher();
        //compute the ith hash of Object obj
        int hash(Object *obj,int i);
        //compute the concatenation of all hash functions i=0,1,..numDimension
        //Usually a user will need this func.
        int hash(Object* obj);

};

#endif