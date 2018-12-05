cmake_minimum_required(VERSION 3.12)
project(PointHashFunction)

set(CMAKE_CXX_STANDARD 17)

link_directories(../test-runner)
include_directories(../test-runner)

add_executable(PointHashFunction main.cpp)
target_link_libraries(PointHashFunction libtest_runner.a)