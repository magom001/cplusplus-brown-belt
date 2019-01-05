cmake_minimum_required(VERSION 3.13)
project(Restructuring)

set(CMAKE_CXX_STANDARD 17)

link_directories(../test-runner)
include_directories(../test-runner)

add_executable(Restructuring main.cpp stats_aggregator.cpp stats_aggregator.h stats_aggregator_test.cpp)


target_link_libraries(Restructuring libtest_runner.a)