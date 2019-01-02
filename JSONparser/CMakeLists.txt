cmake_minimum_required(VERSION 3.13)
project(JSONparser)

set(CMAKE_CXX_STANDARD 17)
link_directories(../test-runner)
include_directories(../test-runner)

add_executable(JSONparser main.cpp json.cpp json.h)
target_link_libraries(JSONparser libtest_runner.a)