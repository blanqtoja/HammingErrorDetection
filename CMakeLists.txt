cmake_minimum_required(VERSION 3.22)
project(HammingErrorDetection)

set(CMAKE_CXX_STANDARD 17)

add_executable(HammingErrorDetection main.cpp
        singleError/singleErrorDetection.cpp
        singleError/singleErrorDetection.h)

