cmake_minimum_required(VERSION 3.12)
project(Cache)

set(CMAKE_CXX_STANDARD 17)
link_directories(../test-runner)
include_directories(../test-runner ../c-plus-plus-profiler)


add_executable(Cache main.cpp Common.h Solution.cpp)
target_link_libraries(Cache libtest_runner.a)