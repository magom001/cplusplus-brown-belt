cmake_minimum_required(VERSION 3.13)
project(LazyValue)

set(CMAKE_CXX_STANDARD 17)


link_directories(../test-runner)
include_directories(../test-runner)

add_executable(LazyValue main.cpp)


target_link_libraries(LazyValue libtest_runner.a)