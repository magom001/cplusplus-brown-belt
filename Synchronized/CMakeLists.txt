cmake_minimum_required(VERSION 3.13)
project(Synchronized)

set(CMAKE_CXX_STANDARD 17)

link_directories(../test-runner)
include_directories(../test-runner)

add_executable(Synchronized main.cpp)

target_link_libraries(Synchronized libtest_runner.a)