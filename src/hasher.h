#ifndef HASHER_H
#define HASHER_H 
#include "Object.h"
//#define GRID_POOL 50
#define WINDOW_SIZE 100
#define GRID_POOL_SIZE 100

//TODO:change when not testing
//--------------
#define private public
//--------------

class Hasher {
    public:
        //virtual int hash(Object *obj) const = 0;
};

//Create an instance per LSHHashtable.
//Call hash(Object*) and the return value will be
//the index of the bucket that Object should be stored.
class PointHasher : public Hasher {
    private:
        //we can set window based on dataset range of values.
        int window = WINDOW_SIZE;
        //size depends on amplification size -evaluated at constructor?
        static double **gridPool ;
        static const int gridPoolSize = GRID_POOL_SIZE;
        int amplificationSize;
        int numDimension;
        int partialHashRange;
        int * selectedGrids;
        void generateGrids();
    public:
        PointHasher();
        //debug only
        PointHasher(int,int,int);
        ~PointHasher();

        //compute the ith hash of Object obj
        int hash(Object *obj,int i) const;

        //compute the concatenation of all hash functions i=0,1,..amplificationSize
        size_t operator() (Object* obj) const;

};

//double **PointHasher::gridPool;

class CurveHasher : public Hasher {
    private:
        


    public: 
        CurveHasher();
        ~CurveHasher();
        int hash(Object *obj);
};

#endif