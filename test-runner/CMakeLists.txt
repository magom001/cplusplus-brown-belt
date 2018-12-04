cmake_minimum_required(VERSION 3.12)
project(test_runner)

set(CMAKE_CXX_STANDARD 17)

add_library(test_runner STATIC test_runner.h test_runner.cpp)