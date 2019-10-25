# Hashing & Searching Algorithms for Vectors and Curves
Task 1, Algorithms Project, DI @ UoA 2019

* The goal of this task is to experiment with algorithms to find Approximate Nearest Neighbors for Vectors/Curves and compare the results with those of brute force search.
* This repository contains 6 different executables for vectors/curves hashing & searching, using LSH, Hypercube, Curve Grids and Curve Random Projection techniques.
* All source/header files, as well as sample input/query data files, are in src directory.
* Implemented on C++ 14
* Build with CMake

## Build & Execution
Run all the following commands in project's root directory.
* **Important First Step!**
    * $ cmake .

#### Vectors LSH
* $ make lsh
* $ ./lsh -d [input file] -q [query file] -k [int] -L [int] -ο [output file]
* Recommended values: k = 5, L = 8
* Approximate Results for dataset of 1.000.000 items: 
    * timeLSH/timeBruteForce = 1/1000
    * Max AF = distanceLSH/distanceTrue = 1.7
    * Average AF = distanceLSH/distanceTrue = 1.1
    
#### Vectors Hypercube
* $ make cube
* $ ./cube -d [input file] -q [query file] -k [int] -M [int] -probes [int] -o [output file]
* WARNING: probes must not be greater than (k * (k+1))/ 2
* Recommended Values: k = 8, M = 600, probes = 30
* Approximate Results for dataset of 1.000.000 items:
    * timeCube/timeBruteForce = 1/1000 
    * Max AF = distanceCube/distanceTrue = 3.2
    * Average AF = distanceCube/distanceTrue = 1.4

#### Curves Grid LSH
* $ make curve_grid_lsh
* $ ./curve_grid_lsh -d [input file] -q [query file] -k_vec [int] -L_grid [int] -o [output file]
* Recommended Values: k_vec = 1, L_grid = 4
* Approximate Results for dataset of 7000 curves (Length limit: 50):
    * timeGridLSH/timeBruteForce = 1/100:
    * Max AF = distanceGridLSH/distanceTrue = 700
    * Average AF = distanceGridLSH/distanceTrue = 78

#### Curves Grid Hypercube    
* $ make curve_grid_hypercube
* $ ./curve_grid_hypercube -d [input file] -q [query file] -k_hypercube [int] -M [int] -probes [int] -o [output file]
* WARNING: probes must not be greater than (k_hypercube * (k_hypercube+1))/ 2
* Recommended Values: k_hypercube = 8, M = 400, probes = 30
* Approximate Results for dataset of 7000 curves (Length limit: 30):
    * timeGridCube/timeBruteForce = 1/50:
    * Max AF = distanceGridCube/distanceTrue = 200
    * Average AF = distanceGridCube/distanceTrue = 5.1
    
#### Curves Projection LSH
* $ make curve_projection_lsh
* $ ./curve_projection_lsh -d [input file] -q [query file] -k_vec [int] -L_vec [int] -e [double] -ο [output file]
* Recommended values: k_vec = 4, L_vec = 5, e = 0.3
* Approximate Results for dataset of 7000 curves (Length limit: 7):
    * timeProjectionLSH/timeBruteForce = 1/5:
    * Max AF = distanceProjectionLSH/distanceTrue = 4.6
    * Average AF = distanceProjectionLSH/distanceTrue = 1.3

#### Curves Projection Hypercube
* $ make curve_projection_hypercube
* $ ./curve_projection_hypercube -d [input file] -q [query file] -k_hypercube [int] -M [int] -probes [int] -e [double] -ο [output file]
* WARNING: probes must not be greater than (k_hypercube * (k_hypercube+1))/ 2
* Recommended values: k_hypercube = 6, M = 100, probes = 20, e = 0.3
* Approximate Results for dataset of 7000 curves (Length limit: 6):
    * timeProjectionCube/timeBruteForce = 1/4:
    * Max AF = distanceProjectionCube/distanceTrue = 65
    * Average AF = distanceProjectionCube/distanceTrue = 3.8

##### Authors
* [Kostis Michailidis](https://github.com/kostismich7) (AM: 1115201500098)
* [Loukas Litsos](https://github.com/lkslts64) (AM: 1115201500082)
