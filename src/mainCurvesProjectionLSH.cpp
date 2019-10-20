#include <iostream>
#include "Projection.h"
#include "ui.h"

using namespace std;

int main(int argc, char* argv[]){

    auto projection = new Projection();

    readArgumentsLSHProjectionCurves(projection, argc, argv);


    return 0;
}