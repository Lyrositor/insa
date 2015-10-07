cmake_minimum_required(VERSION 3.2)
project(insa)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    3if/tp/tp-oo_1/src/Collection.cpp
    3if/tp/tp-oo_1/src/Collection.h
    3if/tp/tp-oo_1/src/main.cpp)

add_executable(insa ${SOURCE_FILES})