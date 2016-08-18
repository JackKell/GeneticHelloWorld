cmake_minimum_required(VERSION 3.3)
project(GeneticHelloWorld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Animal.cpp Animal.h Cannon.cpp Cannon.h Simulation.h CannonSimulation.h CannonSimulation.cpp Gravity.h LivingString.cpp LivingString.h LivingStringSimulation.cpp LivingStringSimulation.h)
add_executable(GeneticHelloWorld ${SOURCE_FILES})