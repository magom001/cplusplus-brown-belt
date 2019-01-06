cmake_minimum_required(VERSION 3.13)
project(Zoo)

set(CMAKE_CXX_STANDARD 17)

link_directories(../test-runner)
include_directories(../test-runner)

add_executable(Zoo main.cpp animals.h)


target_link_libraries(Zoo libtest_runner.a)