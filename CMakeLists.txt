set(CMAKE_LEGACY_CYGWIN_WIN32 0)

cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 14)
#link_libraries(cunit)
project (algorithms_project)


add_executable(Main
        src/mainPointsLSH.cpp
        src/Curve.cpp
        src/Curve.h
        src/Dataset.cpp
        src/Dataset.h
        src/hasher.h
        src/HashTableStruct.cpp
        src/HashTableStruct.h
        src/Object.h
        src/Point.cpp
        src/Point.h
        src/point_hasher.cpp
        src/utils.cpp
        src/utils.h 
        src/ui.cpp 
        src/ui.h 
        src/LSH.cpp 
        src/LSH.h
        src/parse_files.cpp src/parse_files.h)

#add_executable(test_point_hasher
#        src/Curve.cpp
#        src/Curve.h
#        src/Dataset.cpp
#        src/Dataset.h
#        src/hasher.h
#        src/HashTableStruct.cpp
#        src/HashTableStruct.h
#        src/Object.h
#        src/Point.cpp
#        src/Point.h
#        src/point_hasher.cpp
#        src/utils.cpp
#        src/utils.h
#        src/ui.cpp
#        src/ui.h
#        src/LSH.cpp
#        src/LSH.h
#        src/test_point_hasher.cpp
#        )