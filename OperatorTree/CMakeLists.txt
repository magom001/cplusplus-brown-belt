cmake_minimum_required(VERSION 3.13)
project(OperatorTree)

set(CMAKE_CXX_STANDARD 17)

link_directories(../test-runner)
include_directories(../test-runner)

add_executable(OperatorTree main.cpp Common.cpp Common.h)

target_link_libraries(OperatorTree libtest_runner.a)