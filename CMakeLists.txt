cmake_minimum_required(VERSION 3.6)
project(Queue)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Simulation.cpp Queue.h Queue.TestDriver.cpp)
add_executable(Queue ${SOURCE_FILES})