#ifndef ALGORITHMS_PROJECT_CUBE_H
#define ALGORITHMS_PROJECT_CUBE_H
#include <cmath>
#include "LSH.h"

class Cube {
private:

    unsigned int dimension = 3; bool dimension_given = false;
    unsigned int max_checked = 10;
    unsigned int max_probes = 2;

    LSH* lsh;

    unordered_map<int, bool> * binaryMaps;

    unsigned int numberOfVertices;
    vector<Object *> * vertices;
public:

    Cube(){lsh = new LSH();}
    ~Cube(){delete lsh;}

    bool isDimensionGiven() const {return dimension_given;}
    int getDimension() const {return dimension;}
    int getMaxChecked() const {return max_checked;}
    int getMaxProbes() const {return max_probes;}
    auto getLsh() const {return lsh;}
    auto getNumberOfVertices() const {return numberOfVertices;}
    auto getVertices() const {return vertices;}
    auto getBinaryMaps() const {return binaryMaps;}

    void setDimensionGiven(bool given){
        this->dimension_given = given;
    }

    void setDimension(int dimension) {
        this->dimension = dimension;
    }

    void setMaxChecked(int maxChecked) {
        max_checked = maxChecked;
    }

    void setMaxProbes(int maxProbes) {
        max_probes = maxProbes;
    }

    //creates random 0/1 mapping for every entry of hash tables
    void createBinaryMaps() {
        srand(time(nullptr));
        binaryMaps = new unordered_map<int, bool>[dimension];
        auto hashers = lsh->getHashTableStruct()->getHashers();
        auto data = lsh->getDataset()->getData();
        //for every item
        for(auto obj : data){
            //insert it in every map
            for (int i = 0; i < dimension; ++i) {
                binaryMaps[i].insert(make_pair((*hashers.at(i))(obj), rand() % 2 + 0));
            }
        }
    }

    void test_print_binaryMaps(){
        for (int i = 0; i < dimension; i++) {
            cout << "\nBINARY TABLE " << i + 1 << endl;
            for(auto x : binaryMaps[i]){
                cout<<"bucket #"<< x.first << ", value: " << x.second << endl;
            }
        }
    }

    void createVertices() {
        numberOfVertices = pow(2,dimension);
        vertices = new vector<Object *>[numberOfVertices];
        auto data = lsh->getDataset()->getData();
        auto hashers = lsh->getHashTableStruct()->getHashers();
        //for every item, insert it in the right vertex
        for(auto obj : data){
            unsigned int index = 0;
            //construct index
            for (int i = 0; i < dimension; ++i) {
                index <<= 1;
                index |= binaryMaps[i].at((*hashers.at(i))(obj));
            }
            vertices[index].push_back(obj);
        }
    }

    void test_print_vertices(){
        for (int i = 0; i < numberOfVertices; ++i) {
            cout << "VERTEX " << i << endl;
            for(auto obj : vertices[i]){
                cout << obj->getId() << endl;
            }
            cout << endl;
        }
    }
};

#endif //ALGORITHMS_PROJECT_CUBE_H
