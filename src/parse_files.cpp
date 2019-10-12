#include <iostream>
#include <sstream>
#include <fstream>
#include <cfloat>
#include "parse_files.h"
#include "utils.h"

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
    return data;
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