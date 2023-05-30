cmake_minimum_required(VERSION 3.16)
project(KMM)

set(CMAKE_CXX_STANDARD 14)

add_executable(KMM
        main.cpp  structure/graph.cpp structure/graph.h types.h structure/match.cpp structure/match.h structure/index.cpp structure/index.h alg/alg.cpp alg/alg.h)
