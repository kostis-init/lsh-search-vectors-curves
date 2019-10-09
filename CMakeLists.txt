set(CMAKE_LEGACY_CYGWIN_WIN32 0)

cmake_minimum_required (VERSION 2.6)

project (algorithms_project)

add_executable(Main
        src/main.cpp
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
        src/utils.h)