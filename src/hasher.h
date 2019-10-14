#ifndef HASHER_H
#define HASHER_H 
#include "Object.h"
#include "Point.h"
#include "Curve.h"
//#define GRID_POOL 50
#define WINDOW_SIZE 100
#define GRID_POOL_SIZE 100


class Hasher {
    public:
        virtual size_t operator()(Object *obj) const {};
};

//Create an instance per LSHHashtable.
//Call hash(Object*) and the return value will be
//the index of the bucket that Object should be stored.
class PointHasher : public Hasher {
    private:
        //we make only gridPool static (and not e.g window) so we can have
        //multiple datasets with various windowsizes etc.
        static double **gridPool ;
        static const int gridPoolSize = GRID_POOL_SIZE;
        //we can set window based on dataset range of values.
        int window = WINDOW_SIZE;
        int amplificationSize;
        int numDimension;
        int partialHashRange;
        int * selectedGrids;
        //Memoization for powModulo func.
        int *powModuloMem;
        void generateGrids();
    public:
        PointHasher();
        PointHasher(int,int,int);
        ~PointHasher();
        //compute the ith hash of Object obj
        int hash(Point *point,int i) const;
        //compute the concatenation of all hash functions i=0,1,..amplificationSize
        size_t operator() (Object* obj) const;
};

class CurveHasher : public Hasher {
    private:
        int numDimension;
        //delta in slides
        int gridSize;
        //vector t in slides
        double *shiftedGrid;
        //max length of curve (maybe all have the same length
        //- they are already padded-). 
        int max;
        PointHasher *phasher;
        Point *vectorize(double **snapedCurve);
        int isConsecutiveDuplitacate(double **snapedCurve,int i);
        double *snap(Point *point);
        double **snap(Curve *curve);
        double snap(double coordinate,int i);
        //double roundCoordinateV2(Point *point,int i);
    public: 
        CurveHasher();
        //debug
        CurveHasher(int,int,int,int);
        ~CurveHasher();
        size_t operator() (Object *obj) const;
};

#endif