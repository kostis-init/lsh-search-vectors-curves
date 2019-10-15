#include <iostream>
#include <sstream>
#include <fstream>
#include <cfloat>
#include <string.h>
#include <limits>
#include "parse_files.h"
#include "utils.h"
#include "distance.h"

using namespace std;

Dataset* parseInputFilePoints(string filename) {
    if(!file_exists(filename.c_str())){
        cout << "input file does not exist" << endl;
        exit(-1);
    };
    auto data = new Dataset();
    cout << "Parsing input file: " << filename << ", please wait..." << endl;
    ifstream inputFile(filename.c_str());
    string line;
    int size = 0;
    int current_dimension = -1;
    double minCoordinate = DBL_MAX;
    double maxCoordinate = -DBL_MAX;
    while(getline(inputFile, line)){
        //extract item_id
        string item_id = line.substr(0, line.find(' '));
        auto point = new Point(item_id);
        //keep only the coordinates
        line = line.substr(line.find(' ') + 1);
        string token;
        stringstream line_stream(line);
        int dimension = 0;
        //add every coordinate to point
        while(line_stream >> token){
            if(!is_number(token))
                continue;
            auto coordinate = atof(token.c_str());
            minCoordinate = min(coordinate,minCoordinate);
            maxCoordinate = max(coordinate,maxCoordinate);
            point->addCoordinateLast(coordinate);
            dimension++;
        }
        if(current_dimension != -1 && current_dimension != dimension){
            cout << "Error in input file, non stable dimension" << endl;
        }
        current_dimension = dimension;
        size++;
        data->add(point);
    }
    data->setSize(size);
    data->setDimension(current_dimension);
    data->setMax(maxCoordinate);
    data->setMin(minCoordinate);
    //remove this if we dont care about the PointHasher 
    //window value. This call costs to much in terms of
    //processing.
    //data->setMean(meanOfMins(data,1000));
    return data;
}

//Calculate the mean distance of every point with his NN.
//Complexity: numDimension * n^2 / 2 
//We can use a better algorithm instead of bruteforce 
//like kd-tree of octree but it needs some work.
//Use this func only with a Dataset of Points.
int meanOfMins(Dataset *dataset,int limit) {
    double sum = 0;
    int size = dataset->getSize();
    int i=0;
    auto data = dataset->getData();
    for(auto obj : data){
        Point* queryPoint = dynamic_cast<Point*>(obj);
        double distance = numeric_limits<double>::max();
        for(auto candidate : data){
            Point* candidatePoint = dynamic_cast<Point*>(candidate);
            double cur_dist;
            if(candidatePoint != queryPoint
               && (cur_dist = manhattan(*queryPoint, *candidatePoint)) < distance){
                distance = cur_dist;
            }
        }
        i++;
        sum += distance/limit;
        if(i == limit){
            break;
        }
    }
    return sum;
//    auto data = dataset->getData();
//    vector<Point *> points(data.begin(),data.end());
//    double *mins = (double *)malloc(points.size()*sizeof(double));
//    for(int i =0; i < points.size();i++)
//        mins[i] = DBL_MAX;
//    double dist;
//    int NNindex = 0;
//    double mean = 0;
//    for(int i =0; i < points.size();i++) {
//        if (mins[i] != DBL_MAX)
//            continue;
//        for(int j =0; j < points.size();j++) {
//            if (i == j)
//                continue;
//            if ((dist = manhattan(*points.at(i),*points.at(j))) < mins[i]) {
//                mins[i] = dist;
//                NNindex = j;
//            }
//        }
//        //if we find the NN of i, then i is the NN of j too
//        if (mins[NNindex] != DBL_MAX) {
//            mean += mins[i];  //compute mean on the fly
//        } else {
//            mins[NNindex] = mins[i];
//            mean += 2.0 * mins[i];  //compute mean on the fly
//        }
//    }
//    return int(mean) / points.size();
}

QueryDataset* parseQueryFilePoints(string filename){
    if(!file_exists(filename.c_str())){
        cout << "query file does not exist" << endl;
        exit(-1);
    };
    auto data = new QueryDataset();
    cout << "Parsing query file: " << filename << endl;
    ifstream queryFile(filename.c_str());

    //get radius (bonus)
    string radius_line;
    getline(queryFile, radius_line);
    radius_line = radius_line.substr(radius_line.find(' ') + 1);
    data->setRadius(atof(radius_line.c_str()));

    string line;
    int size = 0;
    int current_dimension = -1;
    while(getline(queryFile, line)){
        //extract item_id
        string item_id = line.substr(0, line.find(' '));
        auto point = new Point(item_id);
        //keep only the coordinates
        line = line.substr(line.find(' ') + 1);
        string token;
        stringstream line_stream(line);
        int dimension = 0;
        //add every coordinate to point
        while(line_stream >> token){
            if(!is_number(token))
                continue;
            point->addCoordinateLast(atof(token.c_str()));
            dimension++;
        }
        if(current_dimension != -1 && current_dimension != dimension){
            cout << "Error in query file, non stable dimension" << endl;
            exit(-1);
        }
        current_dimension = dimension;
        size++;
        data->add(point);
    } 
    data->setSize(size);
    data->setDimension(current_dimension);
    return data;
}

