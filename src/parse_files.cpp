#include <iostream>
#include <sstream>
#include <fstream>
#include "parse_files.h"
#include "utils.h"

using namespace std;

DatasetPoints* parseInputFilePoints(string filename) {
    if(!file_exists(filename.c_str())){
        cout << "input file does not exist" << endl;
        exit(-1);
    };
    auto data = new DatasetPoints();
    cout << "Parsing input file: " << filename << endl;
    ifstream inputFile(filename.c_str());
    string line;
    int size = 0;
    int current_dimension = -1;
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
            point->addCoordinateLast(atof(token.c_str()));
            dimension++;
        }
        if(current_dimension != -1 && current_dimension != dimension){
            cout << "Error in input file, non stable dimension" << endl;
            exit(-1);
        }
        current_dimension = dimension;
        size++;
        data->addPoint(point);
    }
    data->setSize(size);
    data->setDimension(current_dimension);
    return data;
}


QueryDatasetPoints* parseQueryFilePoints(string filename){
    if(!file_exists(filename.c_str())){
        cout << "query file does not exist" << endl;
        exit(-1);
    };
    auto data = new QueryDatasetPoints();
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
        data->addPoint(point);
    }
    data->setSize(size);
    data->setDimension(current_dimension);
    return data;
}