cmake_minimum_required(VERSION 3.13)
project(Conveyor)

set(CMAKE_CXX_STANDARD 17)

link_directories(../test-runner)
include_directories(../test-runner)

add_executable(Conveyor main.cpp)

target_link_libraries(Conveyor libtest_runner.a)