cmake_minimum_required(VERSION 3.3)
project(GeneticHelloWorld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Animal.cpp Animal.h)
add_executable(GeneticHelloWorld ${SOURCE_FILES})